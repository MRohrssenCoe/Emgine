#include <iostream>

void RenderManager::Draw() {
	using namespace std;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glLookAt call here
	//glMatrixMode(GL_PROJECTION)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective must be called prior to gluLookAt()!!!
	gluPerspective(90, 16.0 / 9.0, 1, 1000);
	gluLookAt(75, 75, 75, 0, 0, 0, 0, 1, 0);

	//draw all models -> no texturing/coloring yet

	for (int i = 0; i < numModels; i++) {
		//MODELS MUST BE IN TRIANGLES
		//TRIANGLES MUST BE THREE SETS OF THREE COORDINATES
		vector<Vector3f> currentModel = models[i];
		vector<int> ind = indices[i];
		Transform *currentTransform = transforms[i];
		Vector3f s = currentTransform->GetScale();
		Vector3f r = currentTransform->GetRotation();
		Vector3f t = currentTransform->GetTranslation();


		//Transformations
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
		glScalef(s.x, s.y, s.z);
		glRotatef(r.x, 1, 0, 0);
		glRotatef(r.y, 0, 1, 0);
		glRotatef(r.z, 0, 0, 1);
		glTranslatef(t.x, t.y, t.z);

		for (int j = 0; j < ind.size(); j += 3) {
			glBegin(GL_POLYGON);
				glVertex3f(currentModel[ind[j]].x, currentModel[ind[j]].y, currentModel[ind[j]].z);
				glVertex3f(currentModel[ind[j+1]].x, currentModel[ind[j+1]].y, currentModel[ind[j+1]].z);
				glVertex3f(currentModel[ind[j+2]].x, currentModel[ind[j+2]].y, currentModel[ind[j+2]].z);
			glEnd();
		}
		//TODO remove this and only do stuff like this in Tick() funciton
		currentTransform->AddRotation(Vector3f{ 0, 1, 0 });
		glPopMatrix();
	}
	glutSwapBuffers();

}
//TODO evaluate whether copying data into list of models is faster than
//passing a pointer to whereever the model is loaded

int inline RenderManager::AddDrawable(std::vector<Vector3f> model, std::vector<int> ind, Transform* transform) {
	numModels++;
	models.push_back(model);
	indices.push_back(ind);
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