#pragma once
#include "Transform.h"
#include "Component.h"
#include "EngineMain.h"


class Entity {
public:
	Entity();
	void Init();
	void Tick();
	virtual ~Entity();
	int AddComponent(Component* component);
	void RemComponent(int);
	Transform* getTransform();
	void setTransform(Transform t);

private:
	Transform transform;
	std::vector<Component*> components;
	int numComponents = 0;
};


#include "Entity.cpp"