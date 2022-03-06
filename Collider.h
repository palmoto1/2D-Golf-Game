#ifndef COLLIDER_H
#define COLLIDER_H

#include <string>
#include <SDL.h>
#include "Component.h"
#include "Transform.h"

/*class allowing an entity to have colliding properties*/



class Collider: public Component

{
public:
	Collider(const std::string& id);

	Collider(const std::string& id, int xPos, int yPos, int size);

	SDL_Rect& getCollider();


	void initialize() override;

	void update() override;


	void draw() override;


private:

	Transform* transform = nullptr;

	std::string id;
	SDL_Rect collider = { 0, 0, 0, 0 };

	SDL_Rect srcRect = {0, 0, 0, 0};
	SDL_Rect desRect = { 0, 0, 0, 0 };


};

#endif

