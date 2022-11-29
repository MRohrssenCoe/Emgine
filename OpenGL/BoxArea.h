#pragma once
#include "Component.h"
#include "Entity.h"
#include "EngineStructs.h"

//WARNING: This is currently an axis alligned area. It can't be rotated.
class BoxArea : public Component {
public:
	BoxArea() {}
	//Lower left corner, upper right corner
	BoxArea(Vector3, Vector3);
	void Init() override;
	void Tick() override;
private:
	std::vector<Entity> OverlappingEntities;
	Vector3 LowerLeftCorner;
	Vector3 UpperRightCorner;

	Vector3 p1, p2, p4, p5;
};

#include "BoxArea.cpp"