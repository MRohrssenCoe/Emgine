#include "EngineMain.h"
std::vector<Entity> entities;
void mainloop(int value)
{
	//game update
	for (int i = 0; i < entities.size(); i++) {
		entities[i].Tick(/*delta time*/);
	}


	glutPostRedisplay();
	glutTimerFunc(16, mainloop, 0);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	engineGLInit(1600, 900);
	glutTimerFunc(0, mainloop, 0);
	glutMainLoop();
	return 0;
}