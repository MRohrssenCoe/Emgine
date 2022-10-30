#pragma once
#include "EngineStructs.h"
class Transform {
public:
	Transform(float, float, float, float, float, float, float, float, float);
	Transform();
	void SetTranslation(Vector3f);
	void SetScale(Vector3f);
	void SetRotation(Vector3f);
	Vector3f GetTranslation();
	Vector3f GetScale();
	Vector3f GetRotation();
	void AddTranslation(Vector3f);
	void AddScale(Vector3f);
	void AddRotation(Vector3f);
	
private:
	Vector3f Translation;
	Vector3f Scale;
	//Rotation is stored as a rotation along each axis, not some quaternion
	Vector3f Rotation;
};

#include "Transform.cpp"