#pragma once
#include <vector>
class Entity;

class Component{
public:
	virtual void Init() {};
	virtual void Tick() {};
	Entity* GetParent();
	void SetParent(Entity*);
	virtual ~Component() {};
	bool const GetInitFinished();
	void SetInitFinished(bool);
private:
	Entity* parent;
	bool initFinished = false;
};

#include "Component.cpp"