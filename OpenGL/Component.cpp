Entity* Component::GetParent() {
	return parent;
}
bool const Component::GetInitFinished() {
	return initFinished;
}
void Component::SetInitFinished() {
	initFinished = true;
}
void Component::SetParent(Entity* e) {
	parent = e;
}