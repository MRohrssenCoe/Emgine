#include "EngineMain.h"

void mainloop(int value)
{
	glutTimerFunc(16, mainloop, 0);
	//game update
	glutPostRedisplay();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	engineGLInit(1600, 900);
	glutTimerFunc(0, mainloop, 0);
	glutMainLoop();
	return 0;
}