#include "RenderManager.h"
#include "IOSystem.h"
#include "TextureManager.h"
#include "ECS.h"
#include "MeshManager.h"
#include "ShaderManager.h"
#include "MaterialManager.h"
#include "PerlinNoise.h"
#include "UIManager.h"
#include "Voxels.h"
#include "ResourceManager.h"
#include "archiver.h"
#include "AtlasManager.h"

Quaternion getWorldRotation(int objectID) {
    Quaternion rot;
    while (objectID != -1) {
        Transform& tr = ECS::GetComponent<Transform>(objectID);
        rot = tr.rotation * rot;
        objectID = ECS::GetHierarchy().getParent(objectID);
    }
    return rot;
}

Matrix4x4 getCameraView(Matrix4x4 world, int cameraID) {
    Matrix4x4 view;
    Transform& tr = ECS::GetComponent<Transform>(cameraID);
    Vector3 pos = world.getTranslation();
    Quaternion rot = getWorldRotation(cameraID);

    Matrix4x4 R;
    R.setIdentity();
    R.setRotation(Quaternion::Inverse(rot));

    Matrix4x4 T;
    T.setIdentity();
    T.setTranslation(-pos);
    return R * T;
}

TextureStruct RenderManager::renderItemAtlas() {
	int width = 1024;
	int height = 1024;
	int iconSize = 128;
	const int columns = width / iconSize;
	
    int frameBufferMain = TextureManager::CreateFrameBuffer(width, height);
	TextureManager::SetRenderTarget(frameBufferMain);
	
	GraphicsEngine::clear(255);
	GraphicsEngine::clearColorDepthBuffer();

	Matrix4x4 camView;
	camView.setIdentity();
	Matrix4x4 projection;
	projection.setIdentity();
	projection.setOrthoLH(0.0f, iconSize, 0.0f, iconSize, -100.0f, 100.0f);
	
	Matrix4x4 rot;
	Matrix4x4 world;
	Shader* shader = ShaderManager::GetShader(SHADER_icons);
	GraphicsEngine::setShaderProgram(shader);
	GraphicsEngine::setProjectionMatrix(shader, projection);
	GraphicsEngine::setCameraViewMatrix(shader, camView);
	GraphicsEngine::setTexture(TextureManager::GetTextureByID(0), shader);
	GraphicsEngine::setVector4(shader, Color(0).ToVector4());
	for(size_t i = 0; i < MeshManager::getOffsetsCount(); i++) {
		int column = i % columns;
		int row = i / columns;
		int x = column * iconSize;
		int y = row * iconSize;
		GraphicsEngine::setViewPort( x, y, x + iconSize, y + iconSize);

		int meshID = MeshManager::getMeshID(i);
		auto aabb = MeshManager::getMeshByID(meshID).getBoundingBox();

		float angle = 0.0f;
		Vector3 axis;
		Vector2 planeSize;
		Vector2 planeMin;
		
		Vector3 size = aabb.max - aabb.min;
		float areaXY = size.x * size.y;
		float areaXZ = size.x * size.z;
		float areaYZ = size.y * size.z;

		if (areaXY >= areaXZ && areaXY >= areaYZ) {
    		axis = Vector3(1, 0, 0);
   			angle = 0.0f;
			planeSize = Vector2(size.x, size.y);
			planeMin  = Vector2(aabb.min.x, aabb.min.y);
		}
		else if (areaXZ >= areaXY && areaXZ >= areaYZ) {
			axis = Vector3(1, 0, 0);
    		angle = Math::PI * 0.5f;
			planeSize = Vector2(size.x, size.z);
			planeMin  = Vector2(aabb.min.x, aabb.min.z);
		}
		else {
			axis = Vector3(0, 1, 0);
			angle = Math::PI * 0.5f;
    		planeSize = Vector2(size.y, size.z);
    		planeMin  = Vector2(aabb.min.y, aabb.min.z);
		}

		float maxAxis = std::max(planeSize.x, planeSize.y);
		float scaleFactor = (float)(iconSize * 0.9f) / maxAxis;
		Quaternion rotation = Quaternion::FromAxisAngle(axis, angle);
		rot.setIdentity();
		rot.setRotation(rotation);

		world.setIdentity();
		world.setScale(Vector3(scaleFactor, scaleFactor, scaleFactor));
		Vector3 center = aabb.min + size * 0.5f;
		world.setTranslation(Vector3(
			-center.x * scaleFactor,
			-center.y * scaleFactor,
			-center.z * scaleFactor
		));
		world = world * rot;
		GraphicsEngine::setMatrix(shader, world);

		unsigned int number_of_mats = MeshManager::setMeshById(meshID);
		int number_of_triangles = MeshManager::getNumberOfPolygonsByMaterialID(meshID, 0);
		GraphicsEngine::drawTriangles(number_of_triangles, nullptr);
	}

	return TextureManager::getTextureData(frameBufferMain);
}

void RenderManager::renderCamera(Camera &camera, int renderViewIndex) {
	TextureManager::SetRenderTarget(camera.frameBufferIndex);
	int camID = camera.object.getID();
	Matrix4x4 camView = getCameraView(worlds[camID], camID);
	Matrix4x4 projection;
	projection.setIdentity();
	int width, height;
	if (camera.frameBufferIndex == -1) std::tie(width, height) = IOSystem::getWindowSize();
	else std::tie(width, height) = TextureManager::GetTextureSize(camera.frameBufferIndex);

	if(camera.perpective) projection.setPerspectiveFovLH(3.14f / 4, (float)width / height, 0.01f, 1000);
	else projection.setOrthoLH(0, (float)width * camera.focalLength, (float)height * camera.focalLength, 0, -4, 4);

	GraphicsEngine::setViewPort(0, 0, width, height);
	GraphicsEngine::clear(camera.color);
	GraphicsEngine::clearColorDepthBuffer();

	Span<RenderView> renderViews = ECS::GetComponents<RenderView>();
	for (auto& renderView : renderViews) {
		if (renderView.layout != renderViewIndex) continue;
		int objectID = renderView.object.getID();
		if (!ECS::isActive(objectID)) continue;

		// set shape
		unsigned int number_of_mats = MeshManager::setMeshById(renderView.mesh_index);

		// render object
		int number_of_materials = Math::Min(number_of_mats, (unsigned int)renderView.materals.size());
		int offset = 0;
		for (int j = 0; j < number_of_materials; j++) {
			Material material = MaterialManager::Get(renderView.materals[j]);
			int shader_index = material.shader_indexes;
			int texture_index = material.texture_index;
			int texture_index1 = material.texture_index1;
			int mesh_index = renderView.mesh_index;
			Shader *shader_ptr = ShaderManager::GetShader(shader_index);
			// set material
			GraphicsEngine::setShaderProgram(shader_ptr);
			GraphicsEngine::setTime(shader_ptr, Time::time);
			GraphicsEngine::setProjectionMatrix(shader_ptr, projection);
			GraphicsEngine::setCameraViewMatrix(shader_ptr, camView);

			GraphicsEngine::setTexture(TextureManager::GetTextureByID(texture_index), shader_ptr);
			GraphicsEngine::setTexture1(TextureManager::GetTextureByID(texture_index1), shader_ptr);
			GraphicsEngine::setVector4(shader_ptr, material.color.ToVector4());
			GraphicsEngine::setMatrix(shader_ptr, worlds[objectID]);
			if(renderView.object.HasComponent<Voxels>()) {
				GraphicsEngine::setVoxels(shader_ptr, renderView.object.GetComponent<Voxels>().data);
			} 

			int number_of_triangles = MeshManager::getNumberOfPolygonsByMaterialID(mesh_index, j);
			GraphicsEngine::drawTriangles(number_of_triangles, (void *)(offset * sizeof(int)));
			offset += number_of_triangles;
		}
	}

	Shader* textViewShader = ShaderManager::GetShader(SHADER_textShader);
	Span<TextView> textViews = ECS::GetComponents<TextView>();
	GraphicsEngine::setShaderProgram(textViewShader);
	GraphicsEngine::setProjectionMatrix(textViewShader, projection);
	GraphicsEngine::setCameraViewMatrix(textViewShader, camView);
	GraphicsEngine::setTexture(TextureManager::GetTextureByID(TEX_Atlas), textViewShader);
	for (auto& textView : textViews) {
		if (textView.layout != renderViewIndex) continue;
		int objectID = textView.object.getID();
		if (!ECS::isActive(objectID)) continue;

		// set shape
		int mesh_index = textView.getId();
		if(mesh_index == -1) continue;

		// set material
		unsigned int number_of_mats = MeshManager::setMeshById(mesh_index);
		GraphicsEngine::setMatrix(textViewShader, worlds[objectID]);
		int number_of_triangles = MeshManager::getNumberOfPolygonsByMaterialID(mesh_index, 0);
		GraphicsEngine::drawTriangles(number_of_triangles, nullptr);
	}
	
	Shader* uiShader = ShaderManager::GetShader(SHADER_uiShader);
	constexpr float scaleUI = 0.01f;
	if(false) {
		unsigned int number_of_mats = MeshManager::setMeshById(MESH_Plane);
		int planeTriangles = MeshManager::getNumberOfPolygonsByMaterialID(MESH_Plane, 0);
		Span<UIImage> uiImages = ECS::GetComponents<UIImage>();
		GraphicsEngine::setShaderProgram(uiShader);
		GraphicsEngine::setProjectionMatrix(uiShader, projection);
		GraphicsEngine::setCameraViewMatrix(uiShader, camView);
		for (auto& uiImage : uiImages) {
			if (uiImage.layout != renderViewIndex) continue;
			int objectID = uiImage.object.getID();
			if (!ECS::isActive(objectID)) continue;

			GraphicsEngine::setTexture(TextureManager::GetTextureByID(uiImage.texture), uiShader);
			GraphicsEngine::setVector4(uiShader, uiImage.color.ToVector4());

			Vector3 offset = uiImage.getOffset() * scaleUI;
			offset.z *= -1;
			offset.y += 6;
			worlds[objectID].setIdentity();
			worlds[objectID].setScale(uiImage.getComputedSize() * scaleUI);
			worlds[objectID].setTranslation(offset);

			GraphicsEngine::setMatrix(uiShader, worlds[objectID]);
			GraphicsEngine::drawTriangles(planeTriangles, nullptr);
		}

		Span<UIText> uiTextes = ECS::GetComponents<UIText>();
		GraphicsEngine::setShaderProgram(textViewShader);
		GraphicsEngine::setTexture(TextureManager::GetTextureByID(TEX_Atlas), textViewShader);
		
		for (auto& uiText : uiTextes) {
			if (uiText.layout != renderViewIndex) continue;
			int objectID = uiText.object.getID();
			if (!ECS::isActive(objectID)) continue;

			Vector3 offset = uiText.getOffset() * scaleUI;
			offset.z *= -1;
			offset.y += 6;
			worlds[objectID].setIdentity();
			worlds[objectID].setScale(scaleUI);
			worlds[objectID].setTranslation(offset);

			GraphicsEngine::setVector4(textViewShader, uiText.color.ToVector4());
			GraphicsEngine::setMatrix(textViewShader, worlds[objectID]);
			
			int uiTextMesh = uiText.getId();
			if(uiTextMesh == -1) continue;
			unsigned int number_of_mats = MeshManager::setMeshById(uiTextMesh);
			int number_of_triangles = MeshManager::getNumberOfPolygonsByMaterialID(uiTextMesh, 0);
			GraphicsEngine::drawTriangles(number_of_triangles, nullptr);
		}
	}
}
	

void RenderManager::renderUI(int renderViewIndex) {
	TextureManager::SetRenderTarget(-1);
	Span<UIImage> uiImages = ECS::GetComponents<UIImage>();
	Vector2 uiSize = uiImages[0].getComputedSize();

	GraphicsEngine::setViewPort(0, 0, uiSize.x, uiSize.y);
	
	Matrix4x4 camView;
	camView.setIdentity();
	Matrix4x4 projection;
	projection.setIdentity();
	projection.setOrthoLH(0.0f, uiSize.x, 0.0f, uiSize.y, -100.0f, 100.0f);

	Shader* uiShader = ShaderManager::GetShader(SHADER_uiShader);
	unsigned int number_of_mats = MeshManager::setMeshById(MESH_Plane);
	int planeTriangles = MeshManager::getNumberOfPolygonsByMaterialID(MESH_Plane, 0);
	GraphicsEngine::setShaderProgram(uiShader);
	GraphicsEngine::setProjectionMatrix(uiShader, projection);
	GraphicsEngine::setCameraViewMatrix(uiShader, camView);
	for (auto& uiImage : uiImages) {
		if (uiImage.layout != renderViewIndex) continue;
		int objectID = uiImage.object.getID();
		if (!ECS::isActive(objectID)) continue;

		GraphicsEngine::setTexture(TextureManager::GetTextureByID(uiImage.texture), uiShader);
		GraphicsEngine::setVector4(uiShader, uiImage.color.ToVector4());

		Matrix4x4 world;
		world.setIdentity();
		world.setScale(uiImage.getComputedSize());
		world.setTranslation(uiImage.getOffset());

		GraphicsEngine::setMatrix(uiShader, world);
		GraphicsEngine::drawTriangles(planeTriangles, nullptr);
	}

	//ui text
	Shader* textViewShader = ShaderManager::GetShader(SHADER_textShader);
	Span<UIText> uiTextes = ECS::GetComponents<UIText>();
	GraphicsEngine::setShaderProgram(textViewShader);
	GraphicsEngine::setTexture(TextureManager::GetTextureByID(TEX_Atlas), textViewShader);
	GraphicsEngine::setProjectionMatrix(textViewShader, projection);
	GraphicsEngine::setCameraViewMatrix(textViewShader, camView);
	for (auto& uiText : uiTextes) {
		if (uiText.layout != renderViewIndex) continue;
		int objectID = uiText.object.getID();
		if (!ECS::isActive(objectID)) continue;

		worlds[objectID].setIdentity();
		worlds[objectID].setTranslation(uiText.getOffset());

		GraphicsEngine::setVector4(textViewShader, uiText.color.ToVector4());
		GraphicsEngine::setMatrix(textViewShader, worlds[objectID]);
		
		int uiTextMesh = uiText.getId();
		if(uiTextMesh == -1) continue;
		unsigned int number_of_mats = MeshManager::setMeshById(uiTextMesh);
		int number_of_triangles = MeshManager::getNumberOfPolygonsByMaterialID(uiTextMesh, 0);
		GraphicsEngine::drawTriangles(number_of_triangles, nullptr);
	}
}

// #include <chrono>
// float delta = 0;
// int n = 0;
void RenderManager::Render() {
	ECS::UpdateActiveStates();
	// calcualte matrxies
	auto [hierarchy, hierarchySize] = ECS::GetHierarchy().rebuild();
	auto [parents, parentsSize] = ECS::GetHierarchy().getParents();
	for (int i = 0; i < hierarchySize; i++) {
		int objectID = hierarchy[i];
		int parent = parents[objectID];
		if (worlds.size() <= objectID) { worlds.resize(2 * (objectID + 1)); }
		if (!ECS::isActive(objectID)) continue;

		Transform& transform = ECS::GetComponent<Transform>(objectID);
		Matrix4x4 S, R, T;
		S.setIdentity();
		S.setScale(transform.scale);

		R.setIdentity();
		R.setRotation(transform.rotation);

		T.setIdentity();
		T.setTranslation(transform.position);

		Matrix4x4 local = T * R * S;
		if (parent != -1) {
			worlds[objectID] = worlds[parent] * local;
		}
		else {
			worlds[objectID] = local;
		}
	}

	Span<Camera> cameras = ECS::GetComponents<Camera>();
	// auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < cameras.size(); i++) {
		renderCamera(cameras[i], cameras[i].renderLayout);
	}
	renderUI(0);

	// auto end = std::chrono::high_resolution_clock::now();
	// float ms = std::chrono::duration<float, std::milli>(end - start).count();
	// delta += ms;
	// n += 1;
	// printf("Render time: %.3f ms\n", delta / n);
}