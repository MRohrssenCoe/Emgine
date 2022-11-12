#include "OBJ_Loader.h"
#include "ModelComp.h"
#include "EngMath.h"
class Vector3f;
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

	for (int i = 0; i < loader.LoadedVertices.size(); i++) {
		Vector3f v;
		v.x = loader.LoadedVertices[i].Position.X;
		v.y = loader.LoadedVertices[i].Position.Y;
		v.z = loader.LoadedVertices[i].Position.Z;
		model.push_back(v);
	}
	for (int i = 0; i < loader.LoadedIndices.size(); i++) {
		indices.push_back(loader.LoadedIndices[i]);
	}
	//calc and push reference to normals.
	// change all things to be pointers to data stored in this instance.
	//for now do a default transform until this gets integrated with entity
	RM.AddDrawable(&model, &indices, &t);
}
void Model::Tick() {
	if (dynamic) {
		//CalcNormals();
	}
}
void Model::CalcNormals() {
	normals = std::vector<Vector3f>();
	for (int i = 0; i < indices.size(); i += 3) {
		float normal[3] = {0, 0, 0};
		float v1[3] = { model[i].x, model[i].y, model[i].z };
		float v2[3] = { model[i+1].x, model[i+1].y, model[i+1].z };
		float v3[3] = { model[i+2].x, model[i+2].y, model[i+2].z };


		normalVector(v1, v2, v3, normal);
		normals.push_back(Vector3f() = { normal[0], normal[1], normal[2] });
	}
}
Model::~Model() {

}

