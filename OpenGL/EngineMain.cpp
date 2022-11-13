#include "EngineMain.h"
#include "OBJ_Loader.h"
#include "ModelComp.h"
#define PI 3.1415926535
#define PRJ_ORTHO 0
#define PRJ_PERSP 1

#define DISTANCE_STEP .1f
#define ANGLE_STEP .1f
#define MOUSE_SENSITIVITY .1f
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

void myKeyboard(unsigned char key, int x, int y)
{
	CameraInfo c = RM.GetCurrentCameraInfo(); 
	switch (key)
	{
	case 'w':
		
		c.EyeLoc.x += 1;
		break;
	case 'a':
		c.EyeLoc.z -= 1;
		break;
	case 's':
		c.EyeLoc.x -= 1;
		break;
	case 'd':
		c.EyeLoc.z += 1;
		break;
	};
	RM.SetCurrentCameraInfo(c);
	}


/*int prevX, prevY;
void passivemotion(int x, int y)
{
	CameraInfo c = RM.GetCurrentCameraInfo();
	c.LookAtLoc.y = prevY;
	c.LookAtLoc.x = prevX;
	//we have to update here to prevent big jumps between clicks
	prevX = x;
	prevY = y;
	RM.SetCurrentCameraInfo(c);
}
float rho = 3, theta = 0, phi = PI / 2;
void motion(int x, int y)
{
	
	//theta = yaw
	//phi = pitch
	theta += (x - prevX) * ANGLE_STEP * MOUSE_SENSITIVITY;
	phi -= (y - prevY) * ANGLE_STEP * MOUSE_SENSITIVITY;

	prevX = x;
	prevY = y;
	
	glutPostRedisplay();
	
}*/

void myPassiveMotion(int x, int y)
{
	CameraInfo c = RM.GetCurrentCameraInfo();
	c.LookAtLoc.y = y;
	c.LookAtLoc.x = x;

	RM.SetCurrentCameraInfo(c);
}



int main(int argc, char **argv) {

	glutInit(&argc, argv);
	engineGLInit(1600, 900);
	//RM.AddDrawable(model, indices, &t);
	Entity Marquis;
	RM.GetCurrentCameraInfo();

	model = Model("../marquisv.3.obj", true);
	Component* c = &model;
	Marquis.AddComponent(c);
	glutKeyboardFunc(myKeyboard);
	glutPassiveMotionFunc(myPassiveMotion);
	//glutMotionFunc(motion);
	entities.push_back(Marquis);

	glutTimerFunc(0, mainloop, 0);
	glutMainLoop();
	return 0;
}