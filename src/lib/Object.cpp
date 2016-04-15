
#include "Object.h"


//
// constructors
//
Object::Object(Vector _core, float _bodyRadius, float _headRadius)
    : bodyRadius(_bodyRadius), headRadius(_headRadius) {
    core = new Vector(_core);
}
Object::Object() : Object(Vector(0, 0, 0), 1.0f, 0.5f) {}


//
// destructor
//
Object::~Object() {
    delete core;
}


//
// method
//

void Object::setPosition(Vector _core) {
    delete core;
    core = new Vector(_core);
}

void Object::move(Vector diff) {
    Vector _core = *core + diff;

    setPosition(_core);
}

Vector Object::getCore() const {
    return Vector(*core);
}

float Object::getBodyRadius() {
    return bodyRadius;
}

bool Object::isCollided(Object *object) {
    Vector _core = object->getCore();
    float _bodyRadius = object->getBodyRadius();

    return Vector::getDistance(*core, _core) <= (bodyRadius + _bodyRadius);
}