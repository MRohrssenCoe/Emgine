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
		vector<Vector3>* currentModel = models[i];
		vector<int>* ind = indices[i];
		Transform *currentTransform = transforms[i];
		Vector3 s = currentTransform->GetScale();
		Vector3 r = currentTransform->GetRotation();
		Vector3 t = currentTransform->GetTranslation();


		//Transformations
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
		glScalef(s.X, s.Y, s.Z);
		glRotatef(r.X, 1, 0, 0);
		glRotatef(r.Y, 0, 1, 0);
		glRotatef(r.Z, 0, 0, 1);
		glTranslatef(t.X, t.Y, t.Z);

		Vector3* verticesPtr = currentModel->data();
		int* indicesPtr = ind->data();
		for (int j = 0; j < ind->size(); j += 3) {
			glBegin(GL_POLYGON);
				glVertex3f(verticesPtr[indicesPtr[j]].X, verticesPtr[indicesPtr[j]].Y, verticesPtr[indicesPtr[j]].Z);
				glVertex3f(verticesPtr[indicesPtr[j + 1]].X, verticesPtr[indicesPtr[j+1]].Y, verticesPtr[indicesPtr[j+1]].Z);
				glVertex3f(verticesPtr[indicesPtr[j+2]].X, verticesPtr[indicesPtr[j+2]].Y, verticesPtr[indicesPtr[j+2]].Z);
			glEnd();
		}
		//TODO remove this and only do stuff like this in Tick() funciton
		currentTransform->AddRotation(Vector3{ 0, 1, 0 });
		glPopMatrix();
	}
	glutSwapBuffers();

}
//TODO evaluate whether copying data into list of models is faster than
//passing a pointer to whereever the model is loaded

int inline RenderManager::AddDrawable(std::vector<Vector3>* model, std::vector<int>* ind, Transform* transform) {
	numModels++;
	models.push_back(model);
	indices.push_back(ind);
	transforms.push_back(transform);
	return numModels - 1;
}
RenderManager::RenderManager() {

}

void RenderManager::RemDrawable(int id) {
	models.erase(models.begin() + id);
}

int RenderManager::AddMeshVec(std::vector<Mesh>* m) {
	mmmodels.push_back(m);
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