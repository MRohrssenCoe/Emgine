#include "OBJ_Loader.h"
#include "ModelComp.h"
#include "EngMath.h"
class Vector3;
Model::Model(){
}
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
	std::cout << GetParent()->getTransform() << std::endl;

	RM.AddDrawable(&meshes, GetParent()->getTransform());
}
void Model::Tick() {

}

Model::~Model() {

}

