#include "OBJ_Loader.h"
#include "ModelComp.h"
class Vector3f;
Model::Model(std::string modelPath) {
	ModelPath = modelPath;
}
class Transform;
Transform t;

void Model::Init() {
	objl::Loader loader;
	loader.LoadFile(ModelPath);

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
	//for now do a default transform until this gets integrated with entity
	RM.AddDrawable(model, indices, &t);
}
void Model::Tick() {

}
Model::~Model() {

}