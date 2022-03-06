#include "Sprite.h"
#include "GameEngine.h"
#include "AssetManager.h"
#include "Entity.h"
#include <SDL.h>


Sprite::Sprite() = default;

Sprite::Sprite(const std::string& id) {
	setTexture(id);

}



void Sprite::setTexture(const std::string& id) {
	texture = GameEngine::assetManager->getTexture(id);
}


void Sprite::initialize()  {

	transform = &this->getEntity()->getComponent<Transform>();
	srcRect = { 0, 0, transform->getWidth(),  transform->getHeight() };

}
void Sprite::Sprite::update() {

	desRect = { static_cast<int>(transform->getX()), static_cast<int>(transform->getY()), 
		transform->getWidth() * transform->getScale(), transform->getHeight() * transform->getScale() };

}
void Sprite::draw() {
	TextureManager::draw(texture, srcRect, desRect);
}


Sprite::~Sprite() {

}


