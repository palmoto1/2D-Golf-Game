#include "Transform.h"


Transform::Transform() {
	pos.zero();
}


Transform::Transform(int sc) : scale(sc) {
	pos.zero();
}


Transform::Transform(const Vector& p) : pos(p) {}



Transform::Transform(const Vector& p, int h, int w, int sc) : pos(p), height(h), width(w), scale(sc) {}

float Transform::getX() { return pos.x; }
float Transform::getY() { return pos.y; }

int Transform::getHeight() { return height; }
int Transform::getWidth() { return width; }
int Transform::getScale() { return scale; }

Vector& Transform::getPosition() { return pos; }

void Transform::setX(float x) { pos.x = x; }
void Transform::setY(float y) { pos.y = y; }
void Transform::setPosition(const Vector& vec) { pos = vec; }

//updates a position allowing an entity to move forward
void Transform::translate(const Vector& vec) { pos += vec; }
