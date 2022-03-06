#ifndef BALL_H
#define BALL_H
#include <SDL.h>
#include "Component.h"
#include "Transform.h"
#include "Collider.h"
#include "Vector.h"


class Entity;



constexpr float MAX_CHARGE = 500.0f;


class Ball : public Component
{
public:
	Ball(float fr, float sp, const Vector& vel);



	void initialize() override;
	void update() override;

	void checkMapBoundryCollision(float right, float left, float top, float bottom);
	void checkWallCollsion(const SDL_Rect& wallCollider, int concurrentHits);

	bool hasCollision(const SDL_Rect& collider);

	void setAcceleration(float a);
	float getAcceleration() const;
	
	void setVelocity(const Vector& v);
	Vector& getVelocity();

	void setFriction(float f);

	void setAim(float mousePosX, float mousePosY);
	void charge(float charge);
	void shoot();

	void reset();

	~Ball();


private:
	Transform* transform;

	Vector velocity;


	float acceleration;
	float friction;
	float chargeLevel = 0.0f;


};

#endif

