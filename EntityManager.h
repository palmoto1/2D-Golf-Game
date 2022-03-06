#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <vector>
#include <array>
#include "Entity.h"
#include <memory>


//verkar funka nu men inte säkert att minnes städas helt fortsätt fixa
/*managing the game entities. stores the entities and keeps them in different groups*/


// could be any number
constexpr std::size_t MAX_NO_OF_GROUPS = 16;

class EntityManager {

public:


	EntityManager();


	void update();

	void draw();

	void filter();


	void addToEntityGroup(Entity* e, std::size_t n);

	std::vector<Entity*>& getEntityGroup(std::size_t n);


	Entity& addEntity();

	~EntityManager();

private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, MAX_NO_OF_GROUPS> entityGroups;
};



#endif