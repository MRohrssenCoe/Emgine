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
	int AddDrawable(std::vector<Vector3f>*, std::vector<int>*, Transform*);
	//remove drawable by id
	void RemDrawable(int);
	void Draw();
private:
	//list of drawable things - TODO decide data type
	std::vector<std::vector<Vector3f>*> models;
	std::vector<std::vector<int>*> indices;
	std::vector<Transform*> transforms;
	int numModels = 0;
};
RenderManager RM;

void engineGLInit(GLfloat width, GLfloat height);
void Draw();
RenderManager& GetRenderManager();

#include "Renderer.cpp"