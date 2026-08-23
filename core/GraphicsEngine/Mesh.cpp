#include "Mesh.h"
#include "MeshManager.h"

Mesh::Mesh(int* index, int index_size, Vertex* vertex, int vertex_size, unsigned int* materials, unsigned int number_of_materials) {
    indices.assign(index, index + index_size);
    vertices.assign(vertex, vertex + vertex_size);
    this->materials.assign(materials, materials + number_of_materials); 
    syncWithGPU();
}

Mesh::Mesh(Mesh&& mesh) noexcept : indices(std::move(mesh.indices)), vertices(std::move(mesh.vertices)), materials(std::move(mesh.materials)), vao(mesh.vao), iao(mesh.iao) {
    mesh.vao = nullptr;
    mesh.iao = nullptr;
}

Mesh::~Mesh() {
    delete vao;
    delete iao;
}

Mesh& Mesh::operator=(Mesh&& mesh) noexcept {
    if (this != &mesh) {
        delete vao;
        delete iao;

        indices = std::move(mesh.indices);
        vertices = std::move(mesh.vertices);
        materials = std::move(mesh.materials);

        vao = mesh.vao;
        iao = mesh.iao;

        mesh.vao = nullptr;
        mesh.iao = nullptr;
    }
    return *this;
}

void Mesh::syncWithGPU() { 
    if (vao) {
        vao->destroy();
        delete vao;
        vao = nullptr;
    }
    if (iao) {
        iao->destroy();
        delete iao;
        iao = nullptr;
    }
    
    if (!vao) {
        vao = GraphicsEngine::createVertexArrayObject({
            vertices.data(),
            sizeof(Vertex),
            static_cast<unsigned int>(vertices.size())
        });
    }

    if (!iao) {
        iao = GraphicsEngine::createIndexArrayObject({
            reinterpret_cast<unsigned int*>(indices.data()),
            static_cast<unsigned int>(indices.size())
        });
    }
}
	
void Mesh::setMeshOnPipeline() {
    GraphicsEngine::setVertexArrayObject(vao);
    GraphicsEngine::setIndexArrayObject(iao);
}

void Mesh::combineMaterials(int uniqueMaterials) {
    const size_t targetSize = 1 + uniqueMaterials;
    if (materials.size() <= targetSize) return;
    
    for (size_t i = materials.size() - 1; i >= targetSize; --i) {
        materials[i - 1] += materials[i];
    }
    materials.resize(targetSize);
}

BoundingBox Mesh::getBoundingBox() const {
    BoundingBox box;
    if (vertices.empty()) return box;

    box.min = vertices[0].pos;
    box.max = vertices[0].pos;
    for (const Vertex& vertex : vertices) {
        box.min = Vector3::min(box.min, vertex.pos);
        box.max = Vector3::max(box.max, vertex.pos);
    }
    return box;
}