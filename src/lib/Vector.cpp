
#include <iostream>
#include <math.h>

#include "Vector.h"

Vector::Vector() : Vector(0, 0, 0) {}

Vector::Vector(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

Vector::Vector(const Vector &p) : x(p.getX()), y(p.getY()), z(p.getZ()) {}

float Vector::getX() const {
    return x;
}
float Vector::getY() const {
    return y;
}
float Vector::getZ() const {
    return z;
}

void Vector::setX(float _x) {
    x = _x;
}
void Vector::setY(float _y) {
    y = _y;
}
void Vector::setZ(float _z) {
    z = _z;
}
void Vector::set(float _x, float _y, float _z) {
    x = _x;
    y = _y;
    z = _z;
}

void Vector::set(Vector p) {
    x = p.getX();
    y = p.getY();
    z = p.getZ();
}

void Vector::addX(float _x) {
    x += _x;
}
void Vector::addY(float _y) {
    y += _y;
}
void Vector::addZ(float _z) {
    z += _z;
}

Vector Vector::operator+(Vector &p) {
    return Vector(x + p.x, y + p.y, z + p.z);
}
Vector Vector::operator-(Vector &p) {
    return Vector(x - p.x, y - p.y, z - p.z);
}

Vector Vector::operator*(float scale) {
    return Vector(x * scale, y * scale, z * scale);
}

void Vector::normalize() {
    float size = getSize();

    x /= size;
    y /= size;
    z /= size;
}

float Vector::getSize() {
    return sqrtf((x * x) + (y * y) + (z * z));
}

float Vector::getDistance(Vector v1, Vector v2) {
    Vector diff = v1 - v2;

    return diff.getSize();
}

void Vector::print() {
    printf("(%f %f %f)\n", x, y, z);
}