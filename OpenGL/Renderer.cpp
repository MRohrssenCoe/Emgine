#include <iostream>

void RenderManager::Draw() {
	using namespace std;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//glLookAt call here
	//glMatrixMode(GL_PROJECTION)
	//draw all models -> no texturing/coloring yet

	for (int i = 0; i < numModels; i++) {
		//MODELS MUST BE IN TRIANGLES
		//TRIANGLES MUST BE THREE SETS OF THREE COORDINATES
		vector<float> currentModel = models[i];
		Transform currentTransform = transforms[i];
		Vector3f s = currentTransform.GetScale();
		Vector3f r = currentTransform.GetRotation();
		Vector3f t = currentTransform.GetTranslation();


		//Transformations
		glMatrixMode(GL_MODELVIEW);
		/*glScalef(s.x, s.y, s.z);
		glRotatef(r.x, 1, 0, 0);
		glRotatef(r.y, 0, 1, 0);
		glRotatef(r.z, 0, 0, 1);
		glTranslatef(t.x, t.y, t.z);*/

		for (int j = 0; j < currentModel.size(); j += 9) {

			glBegin(GL_POLYGON);
				glVertex3f(currentModel[j], currentModel[j+1], currentModel[j+2]);
				glVertex3f(currentModel[j+3], currentModel[j+4], currentModel[j+5]);
				glVertex3f(currentModel[j+6], currentModel[j+7], currentModel[j+8]);
			glEnd();
		
		}
	}
}
//TODO evaluate whether copying data into list of models is faster than
//passing a pointer to whereever the model is loaded
int RenderManager::AddDrawable(std::vector<float> model, Transform transform) {
	numModels++;
	models.push_back(model);
	transforms.push_back(transform);
	return numModels - 1;
}
RenderManager::RenderManager() {

}

void RenderManager::RemDrawable(int id) {
	models[id].clear();
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
RenderManager& GetRenderManager() {
	return RM;
}