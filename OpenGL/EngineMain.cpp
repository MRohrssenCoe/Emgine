#include "EngineMain.h"
#include "OBJ_Loader.h"
#include "ModelComp.h"
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



objl::Loader loader;
int main(int argc, char **argv) {
	/*loader.LoadFile("../marquisv.3.obj");
	std::vector<Vector3f> model;
	for (int i = 0; i < loader.LoadedVertices.size(); i++) {
		Vector3f v;
		v.x = loader.LoadedVertices[i].Position.X;
		v.y = loader.LoadedVertices[i].Position.Y;
		v.z = loader.LoadedVertices[i].Position.Z;
		model.push_back(v);
	}
	std::vector<int> indices;
	for (int i = 0; i < loader.LoadedIndices.size(); i++) {
		indices.push_back(loader.LoadedIndices[i]);
	}
	Transform t;*/
	glutInit(&argc, argv);
	engineGLInit(1600, 900);
	//RM.AddDrawable(model, indices, &t);
	Model model("../marquisv.3.obj", true);
	std::cout << "model declared" << std::endl;
	model.Init();
	model.Tick();

	glutTimerFunc(0, mainloop, 0);
	glutMainLoop();
	return 0;
}