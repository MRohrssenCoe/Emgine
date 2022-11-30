#pragma once

#include <stdlib.h>
#include "glut.h"
#include <gl/glu.h>
#include <gl/gl.h>
#include "Renderer.h"
#include "Entity.h"
#include "Component.h"
#include <vector>

void SetWindow(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}
std::vector<Entity> entities;
std::vector<Entity>& GetEntities();



float CurMouseX = 0;
float CurMouseY = 0;

float DeltaMouseX = 0;
float DeltaMouseY = 0;

float ForwardAxis = 0;
float RightAxis = 0;