#pragma once
#include "Transform.h"

class Entity {
public:
	Entity();
	virtual void Init();
	virtual void Tick();
	virtual ~Entity();
	template <typename T> void AddComponent(T component);
	template <typename T> void RemComponent(T component);
	Transform getTransform();
	void setTransform(Transform t);

private:
	Transform transform;
//	Components[] components;
};


#include "Entity.cpp"