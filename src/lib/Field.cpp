
#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>

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

void Field::createSnowMan() {

    float currentUserX = (user->getCore()).getX();
    float quarterHeight = height / 4;
    float quarterWidth = width / 4;
    float halfWidth = quarterWidth * 2;
    float halfHeight = quarterHeight * 2;

    // get absolute value of currentUserX
    if (currentUserX < 0) {
        currentUserX *= -1;
    }

    // random coordinates for snowMan
    float x = ((rand() % (int) halfWidth) + currentUserX - quarterWidth);
    float z = -((rand() % (int) halfHeight) + 1.0f);

    if (x > halfWidth) {
        x = halfWidth;
    } else if (x < -halfWidth) {
        x = -halfWidth;
    }


    Vector core(x, bodyRadius, z);
    Vector direction = user->getCore() - core;

    enableNextSnowMan(core, direction);
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

void Field::moveSnowMans(float distance) {
    SnowMan *snowMan;

    float minZ = height / 2;

    for (int i = 0; i < maxSnowManCount; i++) {
        snowMan = snowMans[i];

        // skips disabled snowMan
        if (!snowMan->isEnabled()) {
            continue;
        }

        snowMan->moveToDirection(distance);

        if (!snowMan->isLesserThanMaxX(minZ)) {
            snowMan->disable();

        } else if (snowMan->isCollided(user)) {
            collidedSnowManCount++;
            snowMan->disable();
        }
    }
}

void Field::enableNextSnowMan(Vector _core, Vector _direction) {

    for (int i = 0; i < maxSnowManCount; i++) {
        if (!snowMans[i]->isEnabled()) {

            snowMans[i]->reset(_core, _direction);
            snowMans[i]->enable();
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