#include "OBJ_Loader.h"
#include "ModelComp.h"
#include "EngMath.h"
class Vector3;
Model::Model(){}
Model::Model(std::string modelPath, bool dyn) {
	ModelPath = modelPath;
	dynamic = dyn;
}
class Transform;
Transform t;

void Model::Init() {
	objl::Loader loader;
	loader.LoadFile(ModelPath);
	meshes = loader.LoadedMeshes;

	//fix this to add reference to parent transform
	RM.AddDrawable(&meshes, &t);
}
void Model::Tick() {
	if (dynamic) {
		//CalcNormals();
	}
}
void Model::CalcNormals() {
	normals = std::vector<Vector3>();
	for (int i = 0; i < indices.size(); i += 3) {
		float normal[3] = {0, 0, 0};
		float v1[3] = { model[i].X, model[i].Y, model[i].Z };
		float v2[3] = { model[i+1].X, model[i+1].Y, model[i+1].Z };
		float v3[3] = { model[i+2].X, model[i+2].Y, model[i+2].Z };


		normalVector(v1, v2, v3, normal);
		normals.push_back(Vector3() = { normal[0], normal[1], normal[2] });
	}
}
Model::~Model() {

}

