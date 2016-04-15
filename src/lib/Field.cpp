
#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <math.h>

#include "Field.h"

//
// constructors
//
Field::Field(float _width,
             float _height,
             RGBColor _color,
             float _bodyRadius,
             float _headRadius,
             float _userInitLine
) : width(_width), height(_height), bodyRadius(_bodyRadius), headRadius(_headRadius) {

    Vector userPosition(0.0f, bodyRadius, _userInitLine);

    color = new RGBColor(_color);
    user = new User(userPosition, bodyRadius, headRadius);

    for (int i = 0; i < maxSnowManCount; i++) {
        snowMans[i] = new SnowMan(bodyRadius, headRadius);
    }
}

//
// destructor
//
Field::~Field() {
    delete color;
    delete user;

    for (int i = 0; i < maxSnowManCount; i++) {
        delete snowMans[i];
    }
}

//
// methods
//

void Field::render() {

    // set camera
    user->setGlCamera();

    renderField();
    renderSnowMans();
}

void Field::createSnowMan(float velocity, bool isSuperSnowMan) {

    float currentUserX = (user->getCore()).getX();
    float quarterHeight = height / 4;
    float quarterWidth = width / 4;
    float halfWidth = quarterWidth * 2;

    // random coordinates for snowMan
    float x = (rand() % (int) halfWidth) - quarterWidth + currentUserX;
    float z = -((rand() % (int) quarterHeight) + quarterHeight);

    // ensure snowMan is created inside field
    if (x > halfWidth) {
        x = halfWidth;
    } else if (x < -halfWidth) {
        x = -halfWidth;
    }


    Vector core(x, bodyRadius, z);
    Vector direction = user->getCore() - core;

    enableNextSnowMan(core, direction, velocity, isSuperSnowMan);
}

void Field::moveUser(float deltaX) {
    float halfWidth = width / 2;
    float bound = halfWidth + deltaX;

    // if user is trying to pass bound
    if (((deltaX < 0) && !user->isGreaterThanMinX(-bound)) ||
        ((deltaX > 0) && !user->isLesserThanMaxX(bound))) {
        return;
    }

    user->move(Vector(deltaX, 0, 0));
}

void Field::moveCameraVertically(float height) {
    user->addCameraHeight(height);
}

void Field::moveSnowMans() {
    SnowMan *snowMan;
    Vector userCore = user->getCore();

    float maxZ = (user->getCore()).getZ();
    float distanceToChangeDirection = height / 10;

    for (int i = 0; i < maxSnowManCount; i++) {
        snowMan = snowMans[i];

        // skips disabled snowMan
        if (!snowMan->isEnabled()) {
            continue;
        }

        snowMan->moveToDirection();

        if (!snowMan->isLesserThanMaxX(maxZ)) {
            snowMan->disable();

        } else if (snowMan->isCollided(user)) {
            collidedSnowManCount++;
            snowMan->disable();
        }

        // if snowMan moved enough to change direction
        if (snowMan->getMovedDistance() > distanceToChangeDirection) {
            Vector snowManCore = snowMan->getCore();
            Vector direction = userCore - snowManCore;

            // sign of x value of direction
            float xSign = (direction.getX() > 0) ?
                          1 :
                          -1;

            // absolute values
            float xAbsolute = fabsf(direction.getX());
            float zAbsolute = fabsf(direction.getZ());

            // absolute x can't be larger than absolute z (for proper game)
            if (xAbsolute > zAbsolute) {
                direction.setX(xSign * zAbsolute);
            }

            snowMan->changeDirection(direction);
        }
    }
}

void Field::enableNextSnowMan(Vector _core,
                              Vector _direction,
                              float _velocity,
                              bool isSuperSnowMan) {

    for (int i = 0; i < maxSnowManCount; i++) {
        if (!snowMans[i]->isEnabled()) {

            snowMans[i]->reset(_core, _direction, _velocity);
            snowMans[i]->enable();

            if (isSuperSnowMan) {
                snowMans[i]->setVelocity(_velocity * 2);
                snowMans[i]->setColor(RGBColor(1.0f, 0.0f, 0.0f));
            }

            return;
        }
    }
}

int Field::getCollidedSnowManCount() {
    return collidedSnowManCount;
}

//
// private methods
//

void Field::renderField() {

    color->setGlColor();

    float halfWidth = width / 2;
    float halfHeight = height / 2;

    glBegin(GL_QUADS);
        glVertex3f(-halfWidth, 0.0f, -halfHeight);
        glVertex3f(-halfWidth, 0.0f, halfHeight);
        glVertex3f(halfWidth, 0.0f, halfHeight);
        glVertex3f(halfWidth, 0.0f, -halfHeight);
    glEnd();
}

void Field::renderSnowMans() {

    for (int i = 0; i < maxSnowManCount; i++) {

        // not rendering disabled snowMans
        if (!snowMans[i]->isEnabled()) {
            continue;
        }

        snowMans[i]->render();
    }
}