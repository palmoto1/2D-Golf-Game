#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <array>
#include <iostream>
#include "Component.h"


/*represents entities in the game. can have multiple components that brings different properties to the entities*/


class EntityManager;

static std::size_t ID = 0;
constexpr std::size_t MAX_COMPONENTS = 16;


template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
inline int getID() {
	static std::size_t nextID = ID++;
	return nextID;
}

class Entity {

public:

	Entity(EntityManager& m) : entityManager(m) {}



	void update() {
		for (Component* component : components)
			component->update();
	}
	void draw() {
		for (Component* component : components)
			component->draw();

	}

	bool isActive() const { return active; }

	void inactivate() { active = false; }



	// adds new component to the entity
	template<typename T, typename... Args, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
	T& addComponent(Args&&... args) {
		T* component(new T(std::forward<Args>(args)...));

		component->setEntity(this);
		component->initialize();

		
		components.push_back(component);
		componentArray[getID<T>()] = component;


		return *component;
	}


	template <typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
	T& getComponent() const {
		return *static_cast<T*>(componentArray[getID<T>()]);
	}

	~Entity() {
		for (Component* component : components) {
			delete component;
		}
		components.clear();
	}


private:
	EntityManager& entityManager;
	bool active = true;

	std::vector<Component*> components;
	std::array<Component*, MAX_COMPONENTS> componentArray;
	
};


#endif