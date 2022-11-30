Entity* Component::GetParent() {
	return parent;
}
bool const Component::GetInitFinished() {
	return initFinished;
}
void Component::SetInitFinished(bool b) {
	initFinished = b;
}
void Component::SetParent(Entity* e) {
	parent = e;
}