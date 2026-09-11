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

void Mesh::seperateMeshWithVoxels(int width, int height, int depth) {
    
}

void Mesh::splitTriangleAtCenter(int triangleIndex) {
    const size_t indexOffset = static_cast<size_t>(triangleIndex) * 3;
    uint32_t ia = indices[indexOffset];
    uint32_t ib = indices[indexOffset + 1];
    uint32_t ic = indices[indexOffset + 2];

    const Vector3& a = vertices[ia].pos;
    const Vector3& b = vertices[ib].pos;
    const Vector3& c = vertices[ic].pos;
    Vector3 center = (a + b + c) / 3.0;
    Vertex centerVertex = vertices[ia];
    centerVertex.pos = center;

    uint32_t centerIndex = static_cast<uint32_t>(vertices.size());
    vertices.push_back(centerVertex);
    indices[indexOffset]     = ia;
    indices[indexOffset + 1] = ib;
    indices[indexOffset + 2] = centerIndex;

    indices.push_back(ib);
    indices.push_back(ic);
    indices.push_back(centerIndex);

    indices.push_back(ic);
    indices.push_back(ia);
    indices.push_back(centerIndex);

    materials[0] += 6;
}

ListGraph<float> Mesh::buildGraph() {
    ListGraph<float> graph(trianglesSize(), true);
    for (int i = 0; i < trianglesSize(); ++i) {
        uint32_t a0 = indices[i * 3 + 0];
        uint32_t a1 = indices[i * 3 + 1];
        uint32_t a2 = indices[i * 3 + 2];
        for (int j = i + 1; j < trianglesSize(); ++j) {
            uint32_t b0 = indices[j * 3 + 0];
            uint32_t b1 = indices[j * 3 + 1];
            uint32_t b2 = indices[j * 3 + 2];
            int sharedVertices = 0;
            if (a0 == b0 || a0 == b1 || a0 == b2) ++sharedVertices;
            if (a1 == b0 || a1 == b1 || a1 == b2) ++sharedVertices;
            if (a2 == b0 || a2 == b1 || a2 == b2) ++sharedVertices;
            if (sharedVertices == 2) {
                graph.addEdge(i, j, 1.0f);
            }
        }
    }
    return graph;
}