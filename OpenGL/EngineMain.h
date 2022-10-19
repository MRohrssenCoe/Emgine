#pragma once

#include <stdlib.h>
#include "glut.h"
#include <gl/glu.h>
#include <gl/gl.h>
#include "Renderer.h"

void SetWindow(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}