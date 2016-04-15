
#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <string>

#include "StatusBoard.h"

using namespace std;

string message = "Collided: ";

StatusBoard::StatusBoard(float _x, float _y, int _windowWidth, int _windowHeight)
    : x(_x), y(_y), windowWidth(_windowWidth), windowHeight(_windowHeight) {}

void StatusBoard::setCollidedCount(int _collidedCount) {
    collidedCount = _collidedCount;
}

void StatusBoard::render() {
    string messageToDisplay = message + to_string(collidedCount);

    setOrthographicProjection();

    glPushMatrix();
    glLoadIdentity();

    renderBitmapString(GLUT_BITMAP_HELVETICA_18, messageToDisplay);

    glPopMatrix();

    restorePerspectiveProjection();
}


//
// private methods
//

void StatusBoard::setOrthographicProjection() {
    // switch to projection mode
    glMatrixMode(GL_PROJECTION);

    // save previous matrix which contains the
    //settings for the perspective projection
    glPushMatrix();

    // reset matrix
    glLoadIdentity();

    // set a 2D orthographic projection
    gluOrtho2D(0, windowWidth, windowHeight, 0);

    // switch back to modelview mode
    glMatrixMode(GL_MODELVIEW);
}

void StatusBoard::restorePerspectiveProjection() {

    glMatrixMode(GL_PROJECTION);
    // restore previous projection matrix
    glPopMatrix();

    // get back to modelview mode
    glMatrixMode(GL_MODELVIEW);
}

void StatusBoard::renderBitmapString(void *font, string str) {

    glRasterPos3f(x, y, 0);

    unsigned long length = str.length();

    for (unsigned int i = 0; i < length; i++) {

        char c = str.at(i);

        glutBitmapCharacter(font, c);
    }
}