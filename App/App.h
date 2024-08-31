#pragma once
#include "IOSystem.h"
#include "GraphicsEngine.h"
#include "Matrix4x4.h"
#include "Player.h"
#include "Physic.h"

#define number_of_objects  10000

class App: IOSystem, GraphicsEngine
{
public:
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
	//logic
	Transform transform[number_of_objects];
	SphereCollision collisions[number_of_objects];
	AABB aabb[number_of_objects];
	FirstPersonController player = {&transform[1], &transform[1], 0.1f, 0, 0};

	//shape
	VertexArrayObject* vertexes;
	IndexArrayObject* vertexes_indexes;
	
	//Physic
	Mesh physicHouse;
	VertexArrayObject* vertexes2;
	IndexArrayObject* vertexes_indexes2;
	
	//material
	Shader* shader;
	Shader* shader1;
	Texture* texture[2];

	//world camera
	float t;
	Matrix4x4 cam;
	Matrix4x4 camView;
	Matrix4x4 projection;

	//cube transdtorm data
	float rot_x = 0;
	float rot_y = 0;
	
	//system paramerts
	bool focus = true;
	bool lockCursor = 0;
	bool showCursorParametr = true;
	bool fulscreen = false;
	bool _running = false;
};