#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Vector.h"
#include "Component.h"
#include "EntityManager.h"
#include <SDL_ttf.h>
#include <string>


class Sprite;
class Ball;
class Transform;
class BallController;
class Label;

class GameManager {
public:
	GameManager(EntityManager* m);
	~GameManager();

	EntityManager* getEntityManager() const;
	
	Entity* createBall(const std::string& id, const Vector& pos, const Vector& vel, float friction, float speed, bool controlable, int width, int height, int scale);

	
	Entity* createStaticObject(const std::string& id, const Vector& pos, int width, int height, int scale);

	Entity* createLabel(const std::string& id, const std::string& text, int xPos, int yPos, const SDL_Color& color);

	Entity* createMapCollider(const std::string& id, float posX, float posY, int size, size_t group);




private:
	EntityManager* entityManager;
};


#endif
