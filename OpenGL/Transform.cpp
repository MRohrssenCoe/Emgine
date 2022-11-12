Transform::Transform(float x, float y, float z,
					 float sx, float sy, float sz,
					 float rx, float ry, float rz) {
	Translation.X = x;
	Translation.Y = y;
	Translation.Z = z;
	Scale.X = x;
	Scale.Y = y;
	Scale.Z = z;
	Rotation.X = x;
	Rotation.Y = y;
	Rotation.Z = z;
}

Transform::Transform() {
	Translation.X = 0;
	Translation.Y = 0;
	Translation.Z = 0;
	Scale.X = 1;
	Scale.Y = 1;
	Scale.Z = 1;
	Rotation.X = 0;
	Rotation.Y = 0;
	Rotation.Z = 0;
}

void Transform::SetTranslation(Vector3 v) {
	Translation = v;
}

void Transform::SetScale(Vector3 v) {
	Scale = v;
}

void Transform::SetRotation(Vector3 v) {
	Rotation = v;
}

Vector3 Transform::GetTranslation() {
	return Translation;
}

Vector3 Transform::GetScale() {
	return Scale;
}

Vector3 Transform::GetRotation() {
	return Rotation;
}

void Transform::AddTranslation(Vector3 v) {
	Translation = Translation + v;
}

void Transform::AddScale(Vector3 v) {
	Scale = Scale + v;
}

void Transform::AddRotation(Vector3 v) {
	Rotation = Rotation + v;
}
