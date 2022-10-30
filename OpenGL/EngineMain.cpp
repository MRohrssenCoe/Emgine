#include "EngineMain.h"
int j = 0;
int id1;
void mainloop(int value)
{
	glutTimerFunc(16, mainloop, 0);
	//game update
	if (j >= 300) {
		RM.RemDrawable(id1);
	}
	glutPostRedisplay();
	j++;
}
std::vector<float> mymodel;
std::vector<float> mymodel2;
int main(int argc, char **argv) {
	mymodel.push_back(0.0);
	mymodel.push_back(0.0);
	mymodel.push_back(0.0);
	mymodel.push_back(0.5);
	mymodel.push_back(1.0);
	mymodel.push_back(0.0);
	mymodel.push_back(1.0);
	mymodel.push_back(0.0);
	mymodel.push_back(0.0);
	mymodel2.push_back(-1);
	mymodel2.push_back(-1);
	mymodel2.push_back(0);
	mymodel2.push_back(-1);
	mymodel2.push_back(1);
	mymodel2.push_back(0);
	mymodel2.push_back(0);
	mymodel2.push_back(0);
	mymodel2.push_back(0);
	glutInit(&argc, argv);
	engineGLInit(1600, 900);
	Transform t;
	id1 = RM.AddDrawable(mymodel, t);
	RM.AddDrawable(mymodel2, t);
	
	glutTimerFunc(0, mainloop, 0);

	glutMainLoop();
	return 0;
}