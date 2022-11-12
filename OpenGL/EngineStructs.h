#pragma once
struct Color3f {
	float r, g, b = 0.0;
};

struct Vector3f {
	float x=0.0, y=0.0, z = 0.0;
	Vector3f& operator +(const Vector3f& other) {
		x = other.x + x;
		y = other.y + y;
		z = other.z + z;
		return Vector3f() = {x, y, z};
	}
};

struct CameraInfo {
	Vector3f EyeLoc;
	Vector3f LookAtLoc;
	Vector3f UpVector{ 0, 1, 0 }; // defualt to +y as up axis
	float FOV = 90;
	float NearClip = 1;
	float FarClip = 1000;

};

