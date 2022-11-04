#pragma once
#include <vector>
class Component {
public:
	virtual void Init();
	virtual void Tick();
	virtual ~Component();
};

#include "Component.cpp"