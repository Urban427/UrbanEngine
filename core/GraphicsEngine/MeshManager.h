#pragma once
#include "Mesh.h"

class MeshManager {
public:
    inline static MeshManager& getInstance() { 
        static MeshManager meshManager;
        return meshManager; 
    }

    inline static int addMesh(Mesh&& mesh) {
        auto& instance = getInstance();
        int offset = static_cast<int>(instance.meshes.size());
        instance.offsets.push_back(offset);
        instance.meshes.emplace_back(std::move(mesh));
        return offset;
    }

    inline static int addMesh(Mesh &mesh) {
        auto& instance = getInstance();
        int offset = static_cast<int>(instance.meshes.size());
        instance.offsets.push_back(offset);
        instance.meshes.emplace_back(std::move(mesh));
        return offset;
    }

    inline static int addMeshes(std::vector<Mesh>& meshes) {
        auto& instance = getInstance();
        int offset = static_cast<int>(instance.meshes.size());
        instance.meshes.insert(
            instance.meshes.end(),
            std::make_move_iterator(meshes.begin()),
            std::make_move_iterator(meshes.end())
        );
        instance.offsets.push_back(offset);
        return offset;
    }

    inline static Mesh& getMeshByID(const int id) {
        return getInstance().meshes[id];
    } 

    inline static int setMeshById(int id) {
        getInstance().meshes[id].setMeshOnPipeline();
        return getInstance().meshes[id].getNumberOfMaterials();
    }

    inline static unsigned int getNumberOfPolygonsByMaterialID(int meshID, int materalID) {
        return getInstance().meshes[meshID].getMaterialSize(materalID);
    }

    inline static int getMeshID(int meshFile) {
        return getInstance().offsets[meshFile];
    }

    inline static size_t getOffsetsCount() {
        return getInstance().offsets.size();
    }
private:
    std::vector<Mesh> meshes;
    std::vector<int> offsets;
};