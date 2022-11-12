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
	void CalcNormals();
	std::vector<Mesh> meshes;
	std::vector<Vector3> model;
	std::vector<Material> materials;
	std::vector<Vector3> normals;
	std::vector<int> indices;
};

#include "ModelComp.cpp"