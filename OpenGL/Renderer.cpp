#include <iostream>
#include "EngMath.h"

void SetMaterial(Material*);

void RenderManager::Draw() {
	using namespace std;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	float light_position[3] = {-100, 100, -100};
	GLfloat light_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_specular[] = { .5, .50, .50, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	float globalAmbient = 0.1;
	GLfloat lmodel_ambient[] = { globalAmbient, globalAmbient, globalAmbient, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glEnable(GL_LIGHT0);

	

	glShadeModel(GL_SMOOTH);

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

		std::cout << currentTransform << std::endl;

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
			SetMaterial(&curModel[i][curMeshIndex].MeshMaterial);
			for (int j = 0; j < curModel[i][curMeshIndex].Indices.size(); j += 3) {
				// average out vertex normals to get face normal?
				float normal[3] = { (verticesPtr[indicesPtr[j]].Position.X + verticesPtr[indicesPtr[j+1]].Position.X + verticesPtr[indicesPtr[j+2]].Position.X)/3,
				(verticesPtr[indicesPtr[j]].Position.Y + verticesPtr[indicesPtr[j + 1]].Position.Y + verticesPtr[indicesPtr[j + 2]].Position.Y) / 3,
				(verticesPtr[indicesPtr[j]].Position.Z + verticesPtr[indicesPtr[j + 1]].Position.Z + verticesPtr[indicesPtr[j + 2]].Position.Z) / 3 };
				normalize(normal);

				glBegin(GL_POLYGON);
				glNormal3fv(normal);
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
	transforms = std::vector<Transform*>();
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
	glEnable(GL_LIGHTING);
	glutDisplayFunc(Draw);
	RM = RenderManager();
}
RenderManager& GetRenderManager() {
	return RM;
}

void SetMaterial(Material* m) {
	
	GLfloat mat_ambient[] = { m->Ka.X, m->Ka.Y, m->Ka.Z, 1.0 };
	GLfloat mat_diffuse[] = { m->Kd.X, m->Kd.Y, m->Kd.Z, 1.0 };
	GLfloat mat_specular[] = { m->Ks.X, m->Ks.Y, m->Ks.Z, 1.0 };
	GLfloat mat_shininess[] = { 0. };

	// set material properties
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}