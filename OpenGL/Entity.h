#pragma once
#include "Transform.h"
#include "Component.h"
#include "EngineMain.h"
#include <string>

class Entity {
public:
	Entity();
	Entity(std::string, Transform);
	void Init();
	void Tick();
	virtual ~Entity();
	int AddComponent(Component* component);
	void RemComponent(int);
	Transform* getTransform();
	void setTransform(Transform t);
	std::string GetName();
	void SetName(std::string);
	int numComponents = 0;
	std::vector<Component*> components;


private:
	Transform transform;
	std::string Name;
};


#include "Entity.cpp"