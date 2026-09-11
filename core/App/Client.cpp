#include "Client.h"
#include "GraphicsEngine.h"
#include "Window.h"
#include "RenderManager.h"
#include "WindowsPlatform.h"
#include "Settings.h"
#include "AssetLoader.h"
#include <cstdio>


void Client::create() {
	Settings& s = SettingsSystem::Load();
	IOSystem::addWindow(new Window).create("Sanya lol", 1020, 540, s.fullscreen, s.vsync);
	IOSystem::addkeyBorad(new keyBoard).create();
	IOSystem::addPlatform(new WindowsPlatform).create();
    IOSystem::getWindow().setVSync(s.vsync);
    IOSystem::getInstance().create();

	GraphicsEngine::init();
	GraphicsEngine::clear(Color(0, 0, 0, 1));
	GraphicsEngine::setCullMode(BackFace);

    
	Archive assetArchive;
    #if defined(RELEASE)
        loadArchiveFromFile(assetArchive);
    #else
        loadArchiveFromMainDir(assetArchive);
    #endif
    
    loadAssetsFromPreparedArchive(assetArchive);

    #if defined(PRERELEASE)
        saveArchiveForRelease(assetArchive);
    #endif
}


void Client::update() {
    IOSystem::getInstance().update();
    Scene::Update();
}

// DWORD last = GetTickCount();
// int frames = 0;
void Client::render() {
    RenderManager::onUpdate();
    IOSystem::getWindow().swapBuffers();
    // frames++;
    // DWORD now = GetTickCount();
    // if (now - last >= 1000) {
    //     printf("FPS: %d\n", frames);

    //     frames = 0;
    //     last = now;
    // }
}