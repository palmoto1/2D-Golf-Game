#include "Collider.h"
#include "TextureManager.h"
#include "Entity.h"

Collider::Collider(const std::string& id) : id(id) {

}

Collider::Collider(const std::string& id, int xPos, int yPos, int size) : id(id) {

	collider = { xPos, yPos, size, size };

}

SDL_Rect& Collider::getCollider()
{
	return collider;
}

void Collider::initialize() {
	
	transform = &this->getEntity()->getComponent<Transform>();

	desRect = { collider.x, collider.y, collider.w, collider.h };

}

void Collider::update() {


	
	if (id != "wall" && id != "water") {

		collider = { static_cast<int>(transform->getX()), static_cast<int>(transform->getY()),
		transform->getWidth() * transform->getScale(), transform->getHeight() * transform->getScale() };

		desRect.x = collider.x;
		desRect.y = collider.y;
	}

	

}


void Collider::draw() {
	TextureManager::draw(NULL, srcRect, desRect);
}


