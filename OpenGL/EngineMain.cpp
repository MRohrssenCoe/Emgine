#include "EngineMain.h"
#include "OBJ_Loader.h"
#include "ModelComp.h"

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
Model model;
int main(int argc, char **argv) {

	glutInit(&argc, argv);
	engineGLInit(1600, 900);
	//RM.AddDrawable(model, indices, &t);
	Entity Marquis;
	
	model = Model("../marquisv.3.obj", true);
	Component* c = &model;
	Marquis.AddComponent(c);

	entities.push_back(Marquis);

	glutTimerFunc(0, mainloop, 0);
	glutMainLoop();
	return 0;
}