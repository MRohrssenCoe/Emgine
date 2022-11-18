#pragma once
#include "Component.h"
#include "ModelComp.h"
#include <string>
class LODModelComp : public Component {
public:
	LODModelComp();
	LODModelComp(std::string*, float*, int);
	void Init() override;
	void Tick() override;
	~LODModelComp() override;
private:
	int decideLOD();
	std::vector< std::vector<Mesh>> models;
	std::vector<std::string> modelPaths;
	std::vector<float> distances;
	int modelIndexInRM = -1;
	int numModels = 0;
};

#include "LODModelComponent.cpp"