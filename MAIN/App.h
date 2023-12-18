#pragma once
#include "IOSystem.h"
#include "GraphicsEngine.h"
#include "Matrix4x4.h"

class App
{
public:
	App();
	//~App();

	void onCreate();
	void onUpdate();

	void Move();
	void setInput(float x, float y);
	void setSize(unsigned int width, unsigned int height);

	bool isRunning();
private:
	VertexArrayObject* triangle;
	Shader* shader;
	IndexArrayObject* indexes;
	UniformObject* uniform;
	Texture* texture;

	float scale = 0;
	float x = 0;
	float y = 0;
	float up = 0;
	float rot_x = 0;
	float rot_y = 0;
	Vector3 moveTo;

	bool showCursor = false;
	bool _running = false;
	IOSystem ioSystem;
	GraphicsEngine graphicEngine;
	
	unsigned char* inputState;
	unsigned char* oldinputState;
};

