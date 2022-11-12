#pragma once
#include <vector>

class Entity;

class Component{
public:
	virtual void Init() {};
	virtual void Tick() {};
	Entity* GetParent();
	virtual ~Component() {};
	bool const GetInitFinished();
	void SetInitFinished();
private:
	Entity* parent;
	bool initFinished = false;
};

#include "Component.cpp"