#pragma once
#include "Shader.h"
#include <vector>

class ShaderManager {
private:
    static ShaderManager& getIntsance() {
        static ShaderManager shaderManager;
        return shaderManager;
    }
public:
    static void AddShader(Shader* shader) {
        getIntsance().shaders.push_back(shader);
    }

    static Shader* GetShader(int id) {
        return getIntsance().shaders[id];
    }
private:
	std::vector<Shader*> shaders;
};