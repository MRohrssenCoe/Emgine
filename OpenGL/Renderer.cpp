#include <iostream>
#include "EngMath.h"

void SetMaterial(Material*);

void RenderManager::Draw() {
	using namespace std;

	//glLookAt call here
	//glMatrixMode(GL_PROJECTION)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective must be called prior to gluLookAt()!!!
	gluPerspective(90, 16.0 / 9.0, 1, 1000);
	gluLookAt(eyePos.X, eyePos.Y, eyePos.Z, 0, 0, 0, 0, 1, 0);

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
			//set material
			SetMaterial(&curModel[i][curMeshIndex].MeshMaterial);

			//set lighting
			const GLfloat DIRECTIONAL = 0.0;
			const GLfloat POSITIONAL = 1.0;

			// set global light properties
			GLfloat lmodel_ambient[] = { .4, .4, .4, 1.0 };
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

			GLfloat light_position[] = { -100, 100, -100, DIRECTIONAL };
			GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
			GLfloat light_diffuse[] = { .5, .5, .5, 1.0 };
			GLfloat light_specular[] = { 0.4, 0.4, 0.4, 1.0 };

			// set properties this light 
			glPushMatrix();
			glLoadIdentity();
			glLightfv(GL_LIGHT0, GL_POSITION, light_position);
			glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
			glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
			glPopMatrix();


			//shade model
			glShadeModel(GL_SMOOTH);

			for (int j = 0; j < curModel[i][curMeshIndex].Indices.size(); j += 3) {
				GLfloat normal[3];

				GLfloat v1[3] = { verticesPtr[indicesPtr[j]].Position.X, verticesPtr[indicesPtr[j]].Position.Y, verticesPtr[indicesPtr[j]].Position.Z };
				GLfloat v2[3] = { verticesPtr[indicesPtr[j+1]].Position.X, verticesPtr[indicesPtr[j+1]].Position.Y, verticesPtr[indicesPtr[j+1]].Position.Z };
				GLfloat v3[3] = { verticesPtr[indicesPtr[j+2]].Position.X, verticesPtr[indicesPtr[j+2]].Position.Y, verticesPtr[indicesPtr[j+2]].Position.Z };
				
				// TODO make normals precomputed.
				normalVector(v1, v2, v3, normal);
				for (int i = 0; i < 2; i++)
					normal[i] == -0.f ? 0 : normal[i];
				
				glBegin(GL_POLYGON);
					glNormal3fv(normal);
					glVertex3fv(v1);
					glVertex3fv(v2);
					glVertex3fv(v3);
				glEnd();
			}
		}
		glPopMatrix();
	}
	glutSwapBuffers();

}


RenderManager::RenderManager() {
	transforms = std::vector<Transform*>();
}

void RenderManager::RemDrawable(int id) {
	mmmodels.erase(mmmodels.begin() + id);
}

void RenderManager::ChangeDrawable(int index, std::vector<Mesh>* ptr) {
	mmmodels[index] = ptr;
}

int inline RenderManager::AddDrawable(std::vector<Mesh>* m, Transform* t) {
	numModels++;
	mmmodels.push_back(m);
	transforms.push_back(t);
	return numModels - 1;
}

void Draw() {
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	RM.Draw();
}

void engineGLInit(GLfloat width, GLfloat height) {
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(width, height);

	glutCreateWindow("Emgine");
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glutDisplayFunc(Draw);
	RM = RenderManager();
	RM.eyePos.X = 75;
	RM.eyePos.Y = 75;
	RM.eyePos.Z = 75;
}
RenderManager& GetRenderManager() {
	return RM;
}

void SetMaterial(Material* m) {
	
	GLfloat mat_ambient[] = { m->Kd.X, m->Kd.Y, m->Kd.Z, 1.0 };
	GLfloat mat_diffuse[] = { m->Kd.X, m->Kd.Y, m->Kd.Z, 1.0 };
	GLfloat mat_specular[] = { m->Ks.X, m->Ks.Y, m->Ks.Z, 1.0 };
	GLfloat mat_shininess[] = { m->Ns / 128 };

	// set material properties
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}