Transform::Transform(float x, float y, float z,
					 float sx, float sy, float sz,
					 float rx, float ry, float rz) {
	Translation.x = x;
	Translation.y = y;
	Translation.z = z;
	Scale.x = x;
	Scale.y = y;
	Scale.z = z;
	Rotation.x = x;
	Rotation.y = y;
	Rotation.z = z;
}

Transform::Transform() {
	Translation.x = 0;
	Translation.y = 0;
	Translation.z = 0;
	Scale.x = 1;
	Scale.y = 1;
	Scale.z = 1;
	Rotation.x = 0;
	Rotation.y = 0;
	Rotation.z = 0;
}

void Transform::SetTranslation(Vector3f v) {
	Translation = v;
}

void Transform::SetScale(Vector3f v) {
	Scale = v;
}

void Transform::SetRotation(Vector3f v) {
	Rotation = v;
}

Vector3f Transform::GetTranslation() {
	return Translation;
}

Vector3f Transform::GetScale() {
	return Scale;
}

Vector3f Transform::GetRotation() {
	return Rotation;
}

void Transform::AddTranslation(Vector3f v) {
	Translation = Translation + v;
}

void Transform::AddScale(Vector3f v) {
	Scale = Scale + v;
}

void Transform::AddRotation(Vector3f v) {
	Rotation = Rotation + v;
}
