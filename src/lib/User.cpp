
#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>

#include "User.h"

//
// constructors
//
User::User(Vector _core, float _bodyRadius, float _headRadius)
    : Object(_core, _bodyRadius, _headRadius) {

    gaze = new Vector(0.0f, -0.4f, -1.0f);
    lookUp = new Vector(0.0f, 1.0f, 0.0f);
}


//
// methods
//
Vector User::getCameraPoint() {
    float y = core->getY() + bodyRadius + (2 * headRadius);

    return Vector(core->getX(), y, core->getZ());
}

void User::setGlCamera() {

    Vector cam = getCameraPoint();

    gluLookAt(cam.getX(), cam.getY(), cam.getZ(),
              cam.getX() + gaze->getX(), cam.getY() + gaze->getY(), cam.getZ() + gaze->getZ(),
              lookUp->getX(), lookUp->getY(), lookUp->getZ()
    );
}

bool User::isGreaterThanMinX(float minX) {
    float x = core->getX();

    return (x - bodyRadius) > minX;
}

bool User::isLesserThanMaxX(float maxX) {
    float x = core->getX();

    return (x + bodyRadius) < maxX;
}