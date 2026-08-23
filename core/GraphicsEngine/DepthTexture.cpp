#include "DepthTexture.h"
#include "GraphicConfig.h"

void DepthTexture::init() {
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);


    glGenTextures(1, &depthTexture);
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void DepthTexture::destroy() {
	if (depthTexture  != 0) {
		glDeleteTextures(1, &depthTexture);
		depthTexture = 0;
	}
	if (fbo != 0) {
		glDeleteFramebuffers(1, &fbo);
		fbo = 0;
	}
}

void DepthTexture::bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glViewport(0, 0, width, height);
}

void DepthTexture::unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


TextureStruct DepthTexture::getTextureData()
{
    TextureStruct texture;
    texture.width = width;
    texture.height = height;
    texture.pixels = new int[width * height];

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glReadPixels(0, 0, width, height, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, texture.pixels);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return texture;
}