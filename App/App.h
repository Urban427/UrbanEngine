#pragma once
#include "IOSystem.h"
#include "GraphicsEngine.h"
#include "Matrix4x4.h"

class App: IOSystem, GraphicsEngine
{
public:
	App();
	//~App();

	void GraphicInit();
	void render();
	void setSize(unsigned int width, unsigned int height);
	
	
	void onCreate();
	void onUpdate();


	void Move();
	void setInput(float x, float y);
	
	
	void onDestroy();
	void onFocus();
	void onKillFocus();
	
	
	bool isRunning();
private:
	void calculateCameraView();
private:
	//shape
	VertexArrayObject* vertexes;
	IndexArrayObject* vertexes_indexes;
	
	//material
	Shader* shader;
	UniformObject* uniform;
	Texture* texture;

	//world camera
	Matrix4x4 camView;
	Matrix4x4 projection;

	//cube transdtorm data
	float rot_x = 0;
	float rot_y = 0;
	Vector3 moveTo;
	
	//system paramerts
	bool focus = true;
	bool lockCursor = 0;
	bool showCursorParametr = true;
	bool fulscreen = false;
	bool _running = false;
};