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

	//draw all models 
	for (int i = 0; i < numModels; i++) {
		//get current values to work with
		std:vector<Mesh>* curModel = mmmodels[i];
		Transform* currentTransform = transforms[i];

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

		//iterate through each mesh
		for (int curMeshIndex = 0; curMeshIndex < curModel->size(); curMeshIndex++) {
			Vertex* verticesPtr = curModel[i][curMeshIndex].Vertices.data();
			unsigned int* indicesPtr = curModel[i][curMeshIndex].Indices.data();
			for (int j = 0; j < curModel[i][curMeshIndex].Indices.size(); j += 3) {
				glBegin(GL_POLYGON);
				glVertex3f(verticesPtr[indicesPtr[j]].Position.X, verticesPtr[indicesPtr[j]].Position.Y, verticesPtr[indicesPtr[j]].Position.Z);
				glVertex3f(verticesPtr[indicesPtr[j + 1]].Position.X, verticesPtr[indicesPtr[j + 1]].Position.Y, verticesPtr[indicesPtr[j + 1]].Position.Z);
				glVertex3f(verticesPtr[indicesPtr[j + 2]].Position.X, verticesPtr[indicesPtr[j + 2]].Position.Y, verticesPtr[indicesPtr[j + 2]].Position.Z);
				glEnd();
			}
		}
	}
	glutSwapBuffers();

}
//TODO evaluate whether copying data into list of models is faster than
//passing a pointer to whereever the model is loaded


RenderManager::RenderManager() {

}

void RenderManager::RemDrawable(int id) {
	models.erase(models.begin() + id);
}

int inline RenderManager::AddDrawable(std::vector<Mesh>* m, Transform* t) {
	numModels++;
	mmmodels.push_back(m);
	transforms.push_back(t);
	return numModels - 1;
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