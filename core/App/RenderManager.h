#pragma once
#include "GraphicsEngine.h"
#include "Transform.h"
#include "Scene.h"

class RenderManager {
public:
	inline static RenderManager& getInstance() {
		static RenderManager renderManager;
		return renderManager;
	}
	inline static void onCreate() { getInstance().init(); };
	inline static void onUpdate() { getInstance().Render(); };
private:
	void init();
	void Render();
	void renderCamera(Camera& camera, int renderViewIndex);
	TextureStruct renderItemAtlas();
	void renderUI(int renderViewIndex);
private:
	std::vector<Shader*> shaders;
	std::vector<Matrix4x4> worlds;
};