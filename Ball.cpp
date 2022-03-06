#include "Ball.h"
#include "Entity.h"


Ball::Ball(float fr, float sp, const Vector& vel) : friction(fr), acceleration(sp), velocity(vel) {}


Ball::~Ball() {}

void Ball::initialize()  {
	transform = &this->getEntity()->getComponent<Transform>();

}


//updates the position based on velocity and acceleration
void Ball::update()  { 

	transform->translate(velocity * acceleration);
	acceleration *= friction;

	if (acceleration <= 0.1f)
		acceleration = 0.0f; 

}

//makes the ball bounds of the borders of the window
void Ball::checkMapBoundryCollision(float right, float left, float top, float bottom) {
	if (transform->getX() > right) {
		if (velocity.x > 0)
			velocity.x *= -1.0f;
	}
	if (transform->getX() < left) {
		if (velocity.x < 0)
			velocity.x *= -1.0f;
	}
	if (transform->getY() > top) {
		if (velocity.y > 0)
			velocity.y *= -1.0f;
	}
	if (transform->getY() < bottom) {
		if (velocity.y < 0)
			velocity.y *= -1.0f;
	}
}

//makes the ball bounce of the wall objects
void Ball::checkWallCollsion(const SDL_Rect& wallCollider, int concurrentHits) {

	Collider& collider = this->getEntity()->getComponent<Collider>();
	SDL_Rect temp = collider.getCollider();
	temp.x = collider.getCollider().x + velocity.x;
	if (SDL_HasIntersection(&temp, &wallCollider))
	{
		if (concurrentHits < 2)
			velocity.x *= -1.0f;
		concurrentHits++;
	}

	temp.x = collider.getCollider().x;
	temp.y = collider.getCollider().y + velocity.y;
	if (SDL_HasIntersection(&temp, &wallCollider))
	{
		if (concurrentHits < 2)
			velocity.y *= -1.0f;
		concurrentHits++;
	}

}
bool Ball::hasCollision(const SDL_Rect& collider)
{
	return (SDL_HasIntersection(&this->getEntity()->getComponent<Collider>().getCollider(), &collider));
}




//sets the direction the ball will travel in based on mouse position 
void Ball::setAim(float mousePosX, float mousePosY) {
	Vector direction(mousePosX - transform->getX(), mousePosY - transform->getY());
	direction.normalize();
	velocity = direction;

}



void Ball::charge(float charge) { chargeLevel = charge; }

void Ball::shoot() {


	if (chargeLevel >= MAX_CHARGE)
		chargeLevel = 1000;

	chargeLevel /= 20;
	acceleration = chargeLevel;
	chargeLevel = 0.0f;

}

void Ball::setAcceleration(float a) { acceleration = a; }

float Ball::getAcceleration() const { return acceleration; }



void Ball::setVelocity(const Vector& v) { velocity = v; }

void Ball::setFriction(float f) { friction = f; }

Vector& Ball::getVelocity() { return velocity; }

void Ball::reset() {
	velocity.x = 0.0f;
	velocity.y = 0.0f;
	chargeLevel = 0.0f;
	acceleration = 0.0f;
}

