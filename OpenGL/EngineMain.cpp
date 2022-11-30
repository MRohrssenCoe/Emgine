#include "EngineMain.h"
#include "OBJ_Loader.h"
#include "ModelComp.h"
#include "LODModelComp.h"
#include "BoxArea.h"
#include "Renderer.h"

Model model;
Entity Marquis;
Entity InteriorLoadingZone;
BoxArea box;

Vector3 Position;
float theta = 0;
float phi = 0;
bool W = false, A = false, S = false, D = false;

void mainloop(int value)
{
	//game update
	for (int i = 0; i < entities.size(); i++) {
		entities[i].Tick(/*delta time*/);
	}
	//DeltaMouseX = LastMouseX - CurMouseX;
	//DeltaMouseY = LastMouseY - CurMouseY;
	//LastMouseX = CurMouseX;
	//LastMouseY = CurMouseY;


	//theta += DeltaMouseX / 1000;
	//phi += DeltaMouseY / 1000;

	RightAxis += 1 * D;
	RightAxis -= 1 * A;
	ForwardAxis += 1 * W;
	ForwardAxis -= 1 * S;


	Vector3 calcedLookAt(sin(theta) * cos(phi), sin(phi),cos(theta) * cos(phi));
	
	//forward movement
	RM.eyePos = RM.eyePos + calcedLookAt * ForwardAxis;
	//left right movement
	float RightVec[3];
	float UpVec[3] = { 0, 1,0 };
	float ForwardVec[3] = { calcedLookAt.X, calcedLookAt.Y, calcedLookAt.Z };
	normCrossProduct(ForwardVec, UpVec, RightVec);

	Vector3 rv(RightVec[0], RightVec[1], RightVec[2]);

	RM.eyePos = RM.eyePos + rv * RightAxis;
	RM.lookAtPos = RM.eyePos + calcedLookAt;

	RightAxis = 0;
	RightAxis = 0;
	ForwardAxis = 0;
	ForwardAxis = 0;

	glutPostRedisplay();
	glutTimerFunc(32, mainloop, 0);
}

void KeyboardInput(unsigned char c, int x, int y) {
	ForwardAxis = 0;
	RightAxis = 0;
	if (c == 'w')
		W = true;
	if (c == 's')
		S = true;
	if (c == 'd')
		D = true;
	if (c == 'a')
		A = true;
}

void KeyboardUp(unsigned char c, int x, int y) {
	if (c == 'w')
		W = false;
	if (c == 's')
		S = false;
	if (c == 'd')
		D = false;
	if (c == 'a')
		A = false;
}

void MouseInput(int x, int y) {

	theta -= (float)(x - 800)/1000;
	phi -= (float)(y - 450)/1000;
	glutWarpPointer(800, 450);

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

	glutMotionFunc(MouseInput);
	glutPassiveMotionFunc(MouseInput);
	glutKeyboardFunc(KeyboardInput);
	glutKeyboardUpFunc(KeyboardUp);

	glutTimerFunc(0, mainloop, 0);
	glutMainLoop();
	return 0;
}
std::vector<Entity>& GetEntities() {
	return entities;
}