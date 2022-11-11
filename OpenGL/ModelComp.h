#pragma once
#include "Component.h"
#include <string>

class Model : Component {
public:
	Model(std::string);
	void Init() override;
	void Tick() override;
	~Model() override;
	std::string ModelPath;
};

#include "ModelComp.cpp"