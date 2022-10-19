#pragma once
#include "glut.h"
#include <gl/glu.h>
#include <gl/gl.h>
#include <stdio.h>
#include "EngineStructs.h"

class RenderManager {
public:
	RenderManager();
	//return the id of the drawable thing
	int AddDrawable();
	//remove drawable by id
	void RemDrawable(int);
	void Draw();
private:
	//list of drawable things - TODO decide data type
};
RenderManager RM;

void engineGLInit(GLfloat width, GLfloat height);
void Draw();

#include "Renderer.cpp"