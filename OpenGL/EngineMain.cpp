#include "EngineMain.h"
#include "OBJ_Loader.h"
#include "ModelComp.h"
#include "LODModelComp.h"
#include "BoxArea.h"

LODModelComp model;
Entity Marquis;
Entity InteriorLoadingZone;
BoxArea box;
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
	std::string names[2]{ "../ball.obj","../marquisv.5.obj" };
	float dists[2]{ 0, 75 };
	model = LODModelComp(names, dists, 2);
	Component* c = &model;
	Marquis.AddComponent(c);
	InteriorLoadingZone.AddComponent(&box);
	entities.push_back(Marquis);
	entities.push_back(InteriorLoadingZone);

	glutTimerFunc(0, mainloop, 0);
	glutMainLoop();
	return 0;
}
std::vector<Entity>& GetEntities() {
	return entities;
}