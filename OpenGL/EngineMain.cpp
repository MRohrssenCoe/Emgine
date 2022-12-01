#include "EngineMain.h"
#include "OBJ_Loader.h"
#include "ModelComp.h"
#include "LODModelComp.h"
#include "BoxArea.h"
#include "Renderer.h"
#include <set>
#define LIGHT1 1
#define LIGHT2 2
#define LIGHT3 3
#define LIGHT4 4
#define LIGHT5 5
Model model;
Model indoorsmodel;
Model model2;
Entity Marquis2;
Entity Marquis;
Entity MarquisInterior;
Entity InteriorLoadingZone;
BoxArea box;
Entity Player;
Vector3 Position;

float theta = 0;
float phi = 0;
bool W = false, A = false, S = false, D = false;
int lightChoice = LIGHT1;
bool Outside = true;
bool newDetail = true;
void loadLowerDetail()
{
	
}
void LoadIndoors() {
	if (Outside) {
		entities.clear();
		RM.RemDrawable(0);
		Model* m = (Model*)MarquisInterior.components[0];
		m->SetInitFinished(false);
		entities.push_back(MarquisInterior);
		Outside = false;
	}
	else {
		entities.clear();
		RM.RemDrawable(0);
		Model* m = (Model*)Marquis.components[0];
		m->SetInitFinished(false);
		entities.push_back(Marquis);
		Outside = true;
	}
}
void wireFrame()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
void filledFrame()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
void setLighting(int option) 
{
	/*GLfloat lmodel_ambient[] = {.4, .4, .4, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	GLfloat light_position[] = { 100, 100, 100, 0.0 };
	GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 2.0, 1.0, 1.0 };
	glPushMatrix();
	glLoadIdentity();
	glLightfv(GL_LIGHT1, GL_POSITION, light_position);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glPopMatrix();*/

	switch (lightChoice)
	{
		
	case LIGHT1:
		glDisable(GL_LIGHT0);

		break;
	case LIGHT2:

		break;
	case LIGHT3:

		break;
	case LIGHT4:

		break;
	case LIGHT5:

		break;
	}
}
void mainloop(int value)
{
	//game update
	for (int i = 0; i < entities.size(); i++) {
		if (entities[i].GetName() == "Player")
			entities[i].getTransform()->SetTranslation(RM.eyePos);
		entities[i].Tick(/*delta time*/);
		if (entities[i].GetName() == "Loader") {
			for (int j = 0; j < entities[i].numComponents; i++) {
				if (typeid(*entities[i].components[j]) == typeid(BoxArea)) {
					BoxArea *b = (BoxArea*) entities[i].components[j];
					if (b->PlayerOverlapping)
						LoadIndoors();
				}
			}
		}
	}

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

	//std::cout << RM.eyePos.X << RM.eyePos.Y << RM.eyePos.Z << std::endl;


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
	
	if (c == ' ') {
		LoadIndoors();
	}
	if (c == 'o') {
		glDisable(GL_LIGHT0);
	}
	if (c == 'p') {
		glEnable(GL_LIGHT0);
	}
	if (c == 't') {
		wireFrame();
	}
	if (c == 'r') {
		filledFrame();
	}
	if (c == 'h') {
		loadLowerDetail();
	}
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

void processRightMenuEvents(int option) {
	lightChoice = option;
	glutPostRedisplay();
}

int main(int argc, char **argv) {

	glutInit(&argc, argv);
	engineGLInit(1600, 900);

	Marquis = Entity("Marquis", Transform());
	MarquisInterior = Entity("MarquisInterior", Transform());
	InteriorLoadingZone = Entity("Loader", Transform());
	//Marquis2 = Entity("Marquis2", Transform());
	model = Model("../marquisLOD1.obj");
	indoorsmodel = Model("../insidemarquis.obj");
	//model2 = Model("../marquisv.3.obj");
	box = BoxArea(Vector3(160, 0, -5), Vector3(166, 12, 5));
	Player = Entity("Player", Transform());

	Marquis.AddComponent(&model);
	//Marquis2.AddComponent(&model2);
	MarquisInterior.AddComponent(&indoorsmodel);
	InteriorLoadingZone.AddComponent(&box);
	
	entities.push_back(Marquis);
	//entities.push_back(Marquis2);
	entities.push_back(InteriorLoadingZone);
	entities.push_back(Player);

	//glutMotionFunc(MouseInput);
	glutPassiveMotionFunc(MouseInput);
	glutKeyboardFunc(KeyboardInput);
	glutKeyboardUpFunc(KeyboardUp);
	int lightSubMenu;

	lightSubMenu = glutCreateMenu(processRightMenuEvents);
	glutAddMenuEntry("Light1", LIGHT1);
	glutAddMenuEntry("Light2", LIGHT2);
	glutAddMenuEntry("Light3", LIGHT3);
	glutAddMenuEntry("Light4", LIGHT4);
	glutAddMenuEntry("Light5", LIGHT5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutTimerFunc(0, mainloop, 0);
	glutMainLoop();
	return 0;
}
std::vector<Entity>& GetEntities() {
	return entities;
}