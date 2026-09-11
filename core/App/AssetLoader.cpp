#include "AssetLoader.h"
#include "Color.h"
#include "archiver.h"
#include "AtlasManager.h"
#include "ResourceManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "MeshManager.h"
#include "RenderManager.h"

#define assetsPackName "assetArchive.pck"

void loadAssetsFromPreparedArchive(Archive& assetArchive) {
    Color noneTex(0, 0, 0, 0);
	TextureStruct noneTexture(1, 1);
	noneTexture.getData()[0] = noneTex.ToINT();
	TextureManager::CreateTexture(noneTexture);
	
	Color white(255);
	TextureStruct whiteTexture(1, 1);
	whiteTexture.getData()[0] = white.ToINT();
	TextureManager::CreateTexture(whiteTexture);

    int fileIndex = 0;
	TTFAtlas atlasFinal;
	IOSystem::readTTF(atlasFinal, assetArchive.getFile(fileIndex++));
	atlasFinal.calculateLayout();
	AtlasManager::SetAtlas(atlasFinal);

	TextureStruct atlasTexture;
	if (IOSystem::readImage(atlasTexture, assetArchive.getFile(fileIndex++))) {
		TextureManager::CreateTexture(atlasTexture);
	}

	// create shape points
	MeshManager::addMesh(CreatePlane());
	MeshManager::addMesh(CreateCube());
	MeshManager::addMesh(CreateSphere(0.5f, 32, 32));
	MeshManager::addMesh(CreateCylinder(32));
	MeshManager::addMesh(CreateCapsule(1.0f, 0.5f, 32, 32));

	#define FIELD(name, combineMode) \
		{ \
			std::vector<Mesh> meshes = IOSystem::readFBX(assetArchive.getFile(fileIndex++)); \
			for(auto& mesh : meshes) {mesh.combineMaterials(combineMode); } \
			MeshManager::addMeshes(meshes); \
		}
	MESHES
	#undef FIELD

	// create shader
	#define FIELD(name) \
		ShaderManager::AddShader(GraphicsEngine::createShaderProgram({ \
			assetArchive.getFile(fileIndex++).getPtr(), \
			assetArchive.getFile(fileIndex++).getPtr() \
		}));
	SHADERS
	#undef FIELD


	// create texture
	TextureStruct temp;
	#define FIELD(name) \
		{ \
			CFile& file = assetArchive.getFile(fileIndex++); \
			if (IOSystem::readImage(temp, file)) { \
				TextureManager::CreateTexture(temp); \
			} \
		}
	TEXTURES
	#undef FIELD


	#ifdef Debug 
		CFile itemsFile;
		TextureStruct items = RenderManager::renderItemAtlas();
		IOSystem::writeBMP(items, itemsFile);
		saveCFile("Textures/items.bmp", itemsFile);
	#endif
}

void loadArchiveFromMainDir(Archive& assetArchive) {
    CFile atlasFile = openCFile("Fonts/MyriadWeb.ttf");
    assetArchive.addFile(std::move(atlasFile));
    CFile atlasMapFile = openCFile("Textures/atlas.bmp"); \
    if(atlasMapFile.isEmpty() || isFileOlder("Textures/atlas.bmp", "Fonts/MyriadWeb.ttf")) { \
        TTFAtlas atlas;
        IOSystem::readTTF(atlas, assetArchive.getFile(0));
        seekCFile(assetArchive.getFile(0), 0, SEEK_SET);
        atlas.calculateLayout();

        TextureStruct texture = atlas.toTexture();
        IOSystem::writeBMP(texture, atlasMapFile);
        saveCFile("Textures/atlas.bmp", atlasMapFile);
    }
    assetArchive.addFile(std::move(atlasMapFile));


    #define FIELD(name, combineMode) \
        { \
            CFile blendFile = openCFile("./Models/" #name ".blend"); \
            if(blendFile.isEmpty()) return; \
            CFile checkfile = openCFile("./Models/fbx/" #name ".fbx"); \
            if(checkfile.isEmpty() || isFileOlder("./Models/fbx/" #name ".fbx", "./Models/" #name ".blend")) { \
                std::string command =                                                  \
                    "cmd /c \"\""                                                       \
                    "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Blender\\blender.exe\"" \
                    " \"./Models/" #name ".blend\""                                          \
                    " --python-expr "                                                  \
                    "\"import bpy; bpy.ops.export_scene.fbx(filepath='./Models/fbx/" #name ".fbx')\"" \
                    " -b\"";                                                           \
                int result = std::system(command.c_str()); \
                checkfile = openCFile("./Models/fbx/" #name ".fbx"); \
            } \
            assetArchive.addFile(std::move(checkfile));           \
        }
    MESHES
    #undef FIELD


	// create shader
	#define FIELD(name) \
		{ \
			CFile f1 = openCFile("Shaders/" #name ".vsh"); \
			CFile f2 = openCFile("Shaders/" #name ".fsh"); \
            assetArchive.addFile(std::move(f1)); \
            assetArchive.addFile(std::move(f2)); \
		}
	SHADERS
	#undef FIELD


	// create texture
	#define FIELD(name) \
		{ \
			CFile file = openCFile("Textures/" #name ".png"); \
            assetArchive.addFile(std::move(file)); \
		}
	TEXTURES
	#undef FIELD
}

void loadArchiveFromFile(Archive& assetArchive) {    
    if(!Archive::loadFromFile(assetArchive, "data.pck")) {
        return;
    }
}

void saveArchiveForRelease(Archive& assetArchive) {
    CFile file = assetArchive.toFile();
    saveCFile("./build/GlassWars/data.pck", file);
}