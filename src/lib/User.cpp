
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

    lookUp = new Vector(0.0f, 1.0f, 0.0f);
    frontDirection = new Vector(0.0f, 0.0f, -5 * bodyRadius);
    cameraHeight = bodyRadius + (2 * headRadius);
}


//
// methods
//
Vector User::getCameraPoint() {
    float y = core->getY() + cameraHeight;

    return Vector(core->getX(), y, core->getZ());
}

void User::setGlCamera() {

    Vector cam = getCameraPoint();
    Vector lookAt = *core + *frontDirection;

    gluLookAt(cam.getX(), cam.getY(), cam.getZ(),
              lookAt.getX(), lookAt.getY(), lookAt.getZ(),
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

void User::addCameraHeight(float height) {
    float changedHeight = cameraHeight + height;

    // min camera height = 0
    if (changedHeight >= 0) {
     cameraHeight = changedHeight;
    }
}