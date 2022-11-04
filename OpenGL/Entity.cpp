void Entity::Tick() {
	for (int i = 0; i < components.size(); i++) {
		components[i].Tick();
	}
}