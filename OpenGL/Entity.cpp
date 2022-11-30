//std::vector<Entity>& GetEntities();

Entity::Entity() {
	transform = Transform();
	std::cout << &transform << std::endl;
	Name = "";
}
Entity::Entity(std::string name, Transform t){
	Name = name;
	transform = t;
}
Entity::~Entity() {

}

void Entity::Init() {
}
void Entity::Tick() {
	for (int i = 0; i < components.size(); i++) {
		if (!components[i]->GetInitFinished()) {
			components[i]->Init();
			components[i]->SetInitFinished(true);
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
std::string Entity::GetName() {
	return Name;
}
void Entity::SetName(std::string name) {
	Name = name;
}
