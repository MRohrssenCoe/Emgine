#include "EngineMain.h"
BoxArea::BoxArea(Vector3 lowerLeft, Vector3 upperRight) {
	LowerLeftCorner = lowerLeft;
	UpperRightCorner = upperRight;
}

void BoxArea::Init() {

}

void BoxArea::Tick() {
	for (int i = 0; i < GetEntities().size(); i++) {
		Vector3 t = GetEntities().at(i).getTransform()->GetTranslation();
		if (t.X > LowerLeftCorner.X && t.X < UpperRightCorner.X &&
			t.Y > LowerLeftCorner.Y && t.Y < UpperRightCorner.Y &&
			t.Z > LowerLeftCorner.Z && t.Z < UpperRightCorner.Z) {
			
			if (GetEntities().at(i).GetName() == "Player")
				PlayerOverlapping = true;
		}
	}
}