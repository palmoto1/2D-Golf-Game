#include "EntityManager.h"


EntityManager::EntityManager() {}


void EntityManager::update() {
	for (auto& entity : entities) {
		entity->update();
	}
}



void EntityManager::draw() {
	for (auto& entity : entities) {
		entity->draw();
	}
	for (std::size_t i = 0, ilen = entityGroups.size(); i < ilen; ++i) {
		for (Entity* entity : entityGroups[i]) {
			entity->draw();
		}
	}


}

Entity& EntityManager::addEntity() {
	Entity* entity = new Entity(*this);
	std::unique_ptr<Entity> entityPtr{ entity };
	entities.emplace_back(std::move(entityPtr));
	return *entity;
}


// checks and erases the entities if they are not active/not needed in the game
void EntityManager::filter() {

	for (std::size_t i = 0, ilen = entityGroups.size(); i < ilen; ++i) {
		for (std::vector<Entity*>::iterator j = entityGroups[i].begin(); j != entityGroups[i].end();) {
			if (!(*j)->isActive()) 
				j = entityGroups[i].erase(j);
			
			else
				j++;
		}

	}



	for (std::vector<std::unique_ptr<Entity>>::iterator i = entities.begin(); i != entities.end();) {
		if (!(*i)->isActive()) 
			i = entities.erase(i);		
		else
			i++;
	}
}




void EntityManager::addToEntityGroup(Entity* e, std::size_t i) {
	entityGroups[i].emplace_back(e);
}

std::vector<Entity*>& EntityManager::getEntityGroup(std::size_t i) {
	return entityGroups[i];
}



EntityManager::~EntityManager() {
	
	entities.clear();
	for (std::size_t i = 0, ilen = entityGroups.size(); i < ilen; ++i)
		entityGroups[i].clear();

}
