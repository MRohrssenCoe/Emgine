#include <iostream>

void RenderManager::Draw() {
	using namespace std;
	cout << "In draw!" << endl;
}
RenderManager::RenderManager() {

}

void Draw() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	RM.Draw();
	glutSwapBuffers();
}

void engineGLInit(GLfloat width, GLfloat height) {
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(width, height);

	glutCreateWindow("Emgine");
	glutDisplayFunc(Draw);
	RM = RenderManager();
}
