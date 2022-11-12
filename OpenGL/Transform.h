#pragma once
#include "EngineStructs.h"
class Transform {
public:
	Transform(float, float, float, float, float, float, float, float, float);
	Transform();
	void SetTranslation(Vector3);
	void SetScale(Vector3);
	void SetRotation(Vector3);
	Vector3 GetTranslation();
	Vector3 GetScale();
	Vector3 GetRotation();
	void AddTranslation(Vector3);
	void AddScale(Vector3);
	void AddRotation(Vector3);
	
private:
	Vector3 Translation;
	Vector3 Scale;
	//Rotation is stored as a rotation along each axis, not some quaternion
	Vector3 Rotation;
};

#include "Transform.cpp"