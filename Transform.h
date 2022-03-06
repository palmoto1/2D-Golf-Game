#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "Component.h"
#include "Vector.h"

//these could be any numbers
constexpr int DEFAULT_SIZE = 32;
constexpr int DEFAULT_SCALE = 1;


//determines the position and scale of an entity

class Transform : public Component
{

public:

	Transform();
	Transform(int sc);
	Transform(const Vector& p);
	Transform(const Vector& p, int h, int w, int sc);

	float getX();
	float getY();
	void setX(float x);
	void setY(float y);

	int getHeight();
	int getWidth();
	int getScale();

	Vector& getPosition();
	void setPosition(const Vector& vec);

	void translate(const Vector& vec);

private:
	Vector pos;

	int height = DEFAULT_SIZE;
	int width = DEFAULT_SIZE;
	int scale = DEFAULT_SCALE;


};

#endif

