#pragma once
#include "Transform.h"
#include "Component.h"
#include <variant>

class Entity {
public:
	Entity();
	virtual void Init();
	void Tick();
	virtual ~Entity();
	int AddComponent(Component* component);
	void RemComponent(int);
	Transform getTransform();
	void setTransform(Transform t);

private:
	Transform transform;
	std::vector<Component*> components;
	int numComponents = 0;
};


#include "Entity.cpp"