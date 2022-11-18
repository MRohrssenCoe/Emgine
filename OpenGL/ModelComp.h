#pragma once
#include "Component.h"
#include <string>

class Model : public Component {
public:
	Model();
	Model(std::string);
	void Init() override;
	void Tick() override;
	~Model() override;
	std::string ModelPath;
private:
	std::vector<Mesh> meshes;
};

#include "ModelComp.cpp"