#include "OBJ_Loader.h"
#include "EngMath.h"
Model::Model(){
}
Model::Model(std::string modelPath) {
	ModelPath = modelPath;
}
void Model::Init() {
	objl::Loader loader;
	loader.LoadFile(ModelPath);
	meshes = loader.LoadedMeshes;
	RM.AddDrawable(&meshes, GetParent()->getTransform());
}
void Model::Tick() {

} 

Model::~Model() {

}

