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
	inline static void onUpdate() { getInstance().Render(); };
	static TextureStruct renderItemAtlas();
private:
	void Render();
	void renderCamera(Camera& camera, int renderViewIndex);
	void renderUI(int renderViewIndex);
private:
	std::vector<Matrix4x4> worlds;
};