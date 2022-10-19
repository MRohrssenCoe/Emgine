#pragma once

class Entity {
public:
	Entity();
	virtual void Init();
	virtual void Tick();
	virtual ~Entity();
	template <typename T> void AddComponent(T component);
	template <typename T> void RemComponent(T component);
//private:
//	Components[] components;
};


#include "Entity.cpp"