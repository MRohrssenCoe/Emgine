#include "EngineMain.h"
#include "OBJ_Loader.h"
#include "ModelComp.h"
#include "LODModelComp.h"
std::vector<Entity> entities;
LODModelComp model;
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
	std::string names[2]{ "../marquisv.5.obj", "../ball.obj"};
	float dists[2]{ 0, 75 };
	model = LODModelComp(names, dists, 2);
	Component* c = &model;
	Marquis.AddComponent(c);

	entities.push_back(Marquis);

	glutTimerFunc(0, mainloop, 0);
	glutMainLoop();
	return 0;
}