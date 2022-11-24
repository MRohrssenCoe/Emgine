#include <vector>
#include "OBJ_Loader.h"

float CalcDistance(Vector3 p1, Vector3 p2);
LODModelComp::LODModelComp(){}
LODModelComp::LODModelComp(std::string* modelPathIn, float* dists, int numMods) {
	numModels = numMods;
	
	for (int i = 0; i < numModels; i++) {
		modelPaths.push_back(modelPathIn[i]);
		distances.push_back(dists[i]);
	}
}
void LODModelComp::Init() {
	objl::Loader loader;
	for (int i = 0; i < numModels; i++) {
		loader.LoadFile(modelPaths[i]);
		models.push_back(loader.LoadedMeshes);
	}
	//calc initial distance here
	float dist = CalcDistance(GetParent()->getTransform()->GetTranslation(), RM.eyePos);
	//then get closest LOD
	int initialLOD = decideLOD();
	modelIndexInRM = RM.AddDrawable(&models[initialLOD], GetParent()->getTransform());
}
void LODModelComp::Tick() {

	//if LOD has changed update model in RM
	float dist = CalcDistance(GetParent()->getTransform()->GetTranslation(), RM.eyePos);
	int curLOD = decideLOD();
	RM.ChangeDrawable(modelIndexInRM, &models[curLOD]);
}
LODModelComp::~LODModelComp() {

}

float CalcDistance(Vector3 p1, Vector3 p2) {
	return sqrtf(pow(p2.X - p1.X, 2) + pow(p2.Y - p1.Y, 2) + pow(p2.Z - p1.Z, 2));
}
int LODModelComp::decideLOD() {
	//calc initial distance here
	float dist = CalcDistance(GetParent()->getTransform()->GetTranslation(), RM.eyePos);
	//then get closest LOD
	int outIndex = 0;
	for (int i = 0; i < numModels; i++) {
		if (dist > distances[i]) {
			outIndex = i;
		}
	}
	return outIndex;
}