Entity::Entity() {
	transform = Transform();
	std::cout << &transform << std::endl;
}
Entity::~Entity() {

}
void Entity::Init() {

}
void Entity::Tick() {
	for (int i = 0; i < components.size(); i++) {
		if (!components[i]->GetInitFinished()) {
			components[i]->Init();
			components[i]->SetInitFinished();
		}
		components[i]->Tick();
	}
}
class Component;
int Entity::AddComponent(Component* component) {
	components.push_back(component);
	component->SetParent(this);
	numComponents++;
	return numComponents - 1;
}

void Entity::RemComponent(int i) {
	components.erase(components.begin() + i);
}

Transform* Entity::getTransform() {
	return &transform;
}