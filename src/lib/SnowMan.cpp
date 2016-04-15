
#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#include <GL/glut.h>
#endif

#include "SnowMan.h"

const RGBColor snowManColor = RGBColor::getWhite();
const RGBColor snowManEyeColor = RGBColor::getBlack();
const RGBColor snowManNoseColor = RGBColor(1.0f, 0.5f, 0.5f);

//
// constructors
//

SnowMan::SnowMan(float _bodyRadius, float _headRadius)
    : SnowMan(Vector(), _bodyRadius, _headRadius, Vector()) {}

SnowMan::SnowMan(Vector _core, float _bodyRadius, float _headRadius, Vector _direction)
    : Object(_core, _bodyRadius, _headRadius) {

    direction = new Vector(_direction);
    direction->normalize();

}

//
// destructor
//
SnowMan::~SnowMan() {
    delete direction;
}


//
// methods
//

void SnowMan::render() {

    // push matrix
    glPushMatrix();

    // translate into current position
    float x, y, z;
    x = core->getX();
    y = core->getY();
    z = core->getZ();

    glTranslatef(x, y, z);

    renderBody();
    renderHead();
    renderEyes();
    renderNose();

    // pop matrix
    glPopMatrix();
}

void SnowMan::moveToDirection(float distance) {
    move(*direction * distance);
}

bool SnowMan::isLesserThanMaxX(float maxX) {
    return core->getZ() < maxX;
}

bool SnowMan::isEnabled() {
    return enabled;
}

void SnowMan::enable() {
    enabled = true;
}

void SnowMan::disable() {
    enabled = false;
}

void SnowMan::reset(Vector _core, Vector _direction) {
    core->set(_core);
    direction->set(_direction);

    direction->normalize();
}


//
// private methods
//

void SnowMan::renderBody() {
    snowManColor.setGlColor();

    glutSolidSphere(bodyRadius, 20, 20);
}

void SnowMan::renderHead() {
    snowManColor.setGlColor();

    glTranslatef(0.0f, bodyRadius + headRadius, 0.0f);
    glutSolidSphere(headRadius, 20, 20);
}

void SnowMan::renderEyes() {
    glPushMatrix();

    snowManEyeColor.setGlColor();

    glTranslatef(0.2f * headRadius, 0.40f * headRadius, 0.72f * headRadius);

    glutSolidSphere(0.2f * headRadius ,10, 10);
    glTranslatef(-0.4f * headRadius, 0.0f, 0.0f);
    glutSolidSphere(0.2f * headRadius ,10, 10);

    glPopMatrix();
}

void SnowMan::renderNose() {

    snowManNoseColor.setGlColor();

    glRotatef(0.0f,1.0f, 0.0f, 0.0f);
    glutSolidCone(0.32f * headRadius, 2 * headRadius, 10, 2);
}