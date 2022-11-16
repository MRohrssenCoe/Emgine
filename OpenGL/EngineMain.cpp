#include "EngineMain.h"
#include "OBJ_Loader.h"
#include "ModelComp.h"

std::vector<Entity> entities;
Model model;
Entity Marquis;
void mainloop(int value)
{
	//game update
	for (int i = 0; i < entities.size(); i++) {
		entities[i].Tick(/*delta time*/);
	}
	Vector3 v{ 0, 1, 0 };
	Marquis.getTransform()->AddRotation(v);
	glutPostRedisplay();
	glutTimerFunc(16, mainloop, 0);
}


int main(int argc, char **argv) {

	glutInit(&argc, argv);
	engineGLInit(1600, 900);

	model = Model("../red2.obj", true);
	Component* c = &model;
	Marquis.AddComponent(c);

	entities.push_back(Marquis);

	glutTimerFunc(0, mainloop, 0);
	glutMainLoop();
	return 0;
}