#pragma once
#include "Component.h"
#include <string>

class Model : public Component {
public:
	Model();
	Model(std::string, bool);
	void Init() override;
	void Tick() override;
	~Model() override;
	std::string ModelPath;
	// if a model is dynamic its normals must be recalculated
	bool dynamic;

private:
	std::vector<Mesh> meshes;
};

#include "ModelComp.cpp"