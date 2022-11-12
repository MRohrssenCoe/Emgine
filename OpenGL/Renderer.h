#pragma once
#include "glut.h"
#include <gl/glu.h>
#include <gl/gl.h>
#include <stdio.h>
#include "EngineStructs.h"
#include <vector>
#include "Transform.h"

class RenderManager {
public:
	RenderManager();
	//return the id of the drawable thing
	int AddDrawable(std::vector<Vector3>*, std::vector<int>*, Transform*);
	int AddMeshVec(std::vector<Mesh>*);
	//remove drawable by id
	void RemDrawable(int);
	void Draw();
private:
	// a model may be multiple different meshes, so we will pass pointers to vectors of meshes
	std::vector<std::vector<Mesh>*> mmmodels;
	std::vector<std::vector<Vector3>*> models;
	std::vector<std::vector<int>*> indices;
	std::vector<Transform*> transforms;
	int numModels = 0;
};
RenderManager RM;

void engineGLInit(GLfloat width, GLfloat height);
void Draw();
RenderManager& GetRenderManager();

#include "Renderer.cpp"