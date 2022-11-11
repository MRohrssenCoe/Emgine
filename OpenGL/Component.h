#pragma once
#include <vector>

class Entity;

class Component{
public:
	virtual void Init() {};
	virtual void Tick() {};
	Entity* GetParent();
	virtual ~Component() {};
	
private:
	Entity* parent;
};

#include "Component.cpp"