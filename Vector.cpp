#include "Vector.h"

Vector::Vector()
{
}

Vector::Vector(float x, float y)
{
    this->x = x;
    this->y = y;
}



Vector& Vector::operator+=(const Vector& other)
{
    this->x += other.x;
    this->y += other.y;

    return *this;
}

Vector& Vector::operator-=(const Vector& other)
{
    
    this->x -= other.x;
    this->y -= other.y;

    return *this;
}

Vector& Vector::operator*=(const Vector& other)
{
    this->x *= other.x;
    this->y *= other.y;

    return *this;
}

Vector& Vector::operator/=(const Vector& other)
{
    this->x /= other.x;
    this->y /= other.y;

    return *this;
}


Vector operator+(Vector& left, const Vector& right)
{
    Vector temp(left);
    temp += right;
    return temp;
}

Vector operator-(Vector& left, const Vector& right)
{
    Vector temp(left);
    temp -= right;
    return temp;
}

Vector operator*(Vector& left, const Vector& right)
{
    Vector temp(left);
    temp *= right;
    return temp;
}

Vector operator/(Vector& left, const Vector& right)
{
    Vector temp(left);
    temp /= right;
    return temp;
}

Vector& Vector::zero() {

    this->x = 0.0f;
    this->y = 0.0f;

    return *this;
}

void Vector::normalize()
{
    
    float lenSq = x * x + y * y;
    float len = sqrtf(lenSq);

    x /= len;
    y /= len;
    
}