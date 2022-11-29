#include "EngineMain.h"
#include "OBJ_Loader.h"
#include "ModelComp.h"
#include "LODModelComp.h"
#include "BoxArea.h"

Model model;
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
	std::string names[1]{ "../marquisv.5.obj" };
	float dists[1]{ 0 };

	Marquis = Entity("Marquis", Transform());
	InteriorLoadingZone = Entity("Loader", Transform());
	model = Model("../marquisLOD1.obj");

	Marquis.AddComponent(&model);
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