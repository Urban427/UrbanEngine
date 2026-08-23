#include "TextureManager.h"
#include "GraphicsEngine.h"

TextureManager *TextureManager::textureManager = new TextureManager();

#define TYPE_BITS 2

#define TYPE_MASK ((1u << TYPE_BITS) - 1u)
#define TYPE_SHIFT 30

#define VALID_BIT (1u << (TYPE_SHIFT - 1))

#define INDEX_MASK ((1u << (TYPE_SHIFT - 2)) - 1u)

#define TEXTURE       0
#define FRAMEBUFFER   1
#define DEPTH_TEXTURE 2


unsigned int MakeID(unsigned int type, bool valid, unsigned int index) {
    return ((type & TYPE_MASK) << TYPE_SHIFT)
         | (valid ? VALID_BIT : 0)
         | (index & INDEX_MASK);
}

unsigned int GetType(unsigned int id) {
    return (id >> TYPE_SHIFT) & TYPE_MASK;
}

unsigned int GetIndex(unsigned int id)
{
	return id & INDEX_MASK;
}




unsigned int TextureManager::GetTextureByID(unsigned int id)
{
	unsigned int index = GetIndex(id);
	if (GetType(id) == TEXTURE) {
		if (index < textureManager->textures.size())
			return textureManager->textures[index]->getID();
	}
	else {
		if (index < textureManager->frameBuffers.size())
			return textureManager->frameBuffers[index]->getColorTexture();
	}
	return textureManager->textures[0]->getID();
}

unsigned int TextureManager::CreateTexture(const TextureStruct desc) {
	unsigned int index;
	if (!textureManager->freeTextureIDs.empty()) {
		index = textureManager->freeTextureIDs.top();
		textureManager->freeTextureIDs.pop();
		// delete textureManager->textures[index];
		textureManager->textures[index] = new Texture(desc);
	}
	else {
		index = static_cast<unsigned int>(textureManager->textures.size());
		textureManager->textures.push_back(new Texture(desc));
	}
	return MakeID(TEXTURE, true, index);
}

unsigned int TextureManager::CreateFrameBuffer(int width, int height) {
	unsigned int index;
	if (!textureManager->freeFramebufferIDs.empty()) {
		index = textureManager->freeFramebufferIDs.top();
		textureManager->freeFramebufferIDs.pop();
		delete textureManager->frameBuffers[index];
		textureManager->frameBuffers[index] = new FrameBuffer();
	}
	else {
		index = static_cast<unsigned int>(textureManager->frameBuffers.size());
		textureManager->frameBuffers.push_back(new FrameBuffer(width, height));
	}
	return MakeID(FRAMEBUFFER, true, index);
}
	
unsigned int TextureManager::CreateDepthTexture	(int width, int height) {
	unsigned int index = static_cast<unsigned int>(textureManager->depthTextures.size());
	textureManager->depthTextures.push_back(new DepthTexture(width, height));
	return MakeID(DEPTH_TEXTURE, true, index);
}

void TextureManager::DeleteTexture(unsigned int id) {
	unsigned int index = GetIndex(id);
	if (GetType(id) == TEXTURE) {
		if (index < textureManager->textures.size()) {
			delete textureManager->textures[index];
			textureManager->textures[index] = nullptr;
			textureManager->freeTextureIDs.push(index);
		}
	}
	else {
		if (index < textureManager->frameBuffers.size()) {
			delete textureManager->frameBuffers[index];
			textureManager->frameBuffers[index] = nullptr;
			textureManager->freeFramebufferIDs.push(index);
		}
	}
}

void TextureManager::SetRenderTarget(unsigned int id) {
	unsigned int index = GetIndex(id);
	if (GetType(id) == TEXTURE || id == -1) {
		GraphicsEngine::setRenderTargetWindow();
	}
	else if (GetType(id) == FRAMEBUFFER) {
		textureManager->frameBuffers[index]->bind();
	}
	else {
		textureManager->depthTextures[index]->bind();
	}
}

void TextureManager::ResizeFrameBuffer(unsigned int id, int width, int height)
{
	unsigned int index = GetIndex(id);
	if (GetType(id) == TEXTURE || id == -1) {
		return;
	}
	textureManager->frameBuffers[index]->resize(width, height);
}

std::pair<int, int> TextureManager::GetTextureSize(unsigned int id) {
	unsigned int index = GetIndex(id);
	if (GetType(id) == TEXTURE) 
		return textureManager->textures[index]->getSize();
	return textureManager->frameBuffers[index]->getSize();
}

TextureStruct TextureManager::getTextureData(unsigned int id) {
	unsigned int index = GetIndex(id);
	switch(GetType(id)) {
		case(TEXTURE) : return TextureStruct();
		case(DEPTH_TEXTURE) : return textureManager->depthTextures[index]->getTextureData();;
	}
	return textureManager->frameBuffers[index]->getTextureData();
}