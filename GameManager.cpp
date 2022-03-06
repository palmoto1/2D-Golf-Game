#include "Gamemanager.h"
#include "Transform.h"
#include "Sprite.h"
#include "Ball.h"
#include "Transform.h"
#include "BallController.h"
#include "Label.h"
#include "EntityGroups.h"
#include "Entity.h"


GameManager::GameManager(EntityManager* m): entityManager(m) {

}

GameManager::~GameManager() {

}

EntityManager* GameManager::getEntityManager() const
{
	return entityManager;
}


Entity* GameManager::createBall(const std::string& id, const Vector& pos, const Vector& vel, float friction, float speed, bool controlable, int width, int height, int scale)
{
	auto& ball(entityManager->addEntity());
	ball.addComponent<Transform>(pos, width, height, scale);
	ball.addComponent<Sprite>(id);
	ball.addComponent<Ball>(friction, speed, vel);
	ball.addComponent<Collider>(id);

	if (controlable)
		ball.addComponent<BallController>();

	entityManager->addToEntityGroup(&ball, EntityGroup::MOVING_OBJECT_GROUP);
	return &ball;

}

Entity* GameManager::createStaticObject(const std::string& id, const Vector& pos, int width, int height, int scale)
{
	auto& object(entityManager->addEntity());
	object.addComponent<Transform>(pos, width, height, scale);
	object.addComponent<Sprite>(id);
	object.addComponent<Collider>(id);

	entityManager->addToEntityGroup(&object, EntityGroup::NON_MOVING_OBJECT_GROUP);
	return &object;

}

Entity* GameManager::createLabel(const std::string& id, const std::string& text, int xPos, int yPos, const SDL_Color& color)
{
	auto& label(entityManager->addEntity());
	label.addComponent<Label>(xPos, yPos, text, id, color);

	entityManager->addToEntityGroup(&label, EntityGroup::UI_GROUP);
	return &label;
}

Entity* GameManager::createMapCollider(const std::string& id, float posX, float posY, int size, size_t group)
{
	auto& col(entityManager->addEntity());
	col.addComponent<Collider>(id, posX, posY, size);
	entityManager->addToEntityGroup(&col, group);
	return &col;
}


