
#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>

// include custom libs
#include "lib/Field.h"
#include "lib/StatusBoard.h"

using namespace std;

int windowWidth(640), windowHeight(640);
int windowPositionX(100), windowPositionY(100);

// status board position
int boardX(50), boardY(30);

// snowMan movement distance
float snowManMovementDistance = 0.1f;

float fieldWidth(100.0f), fieldHeight(100.0f);

// z coordinate of initial user position
float userInitLine = 5.0f;

float bodyRadius(0.75f), headRadius(0.25f);

// user movement along x axis
float deltaMove(0);

// for creating snowMans
int elapsedSecond(0);

Field *field;
RGBColor fieldColor(0.9f, 0.9f, 0.9f);

StatusBoard *board;

// function declarations
void renderScene();
void resizeScene(int width, int height);
void pressKey(int key, int xx, int yy);
void releaseKey(int key, int xx, int yy);
void handleMovement();

// main
int main(int argc, char *argv[]) {

    // for rand function
    srand((unsigned int) time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    // initialize window
    glutInitWindowPosition(windowPositionX, windowPositionY);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("CG Hw2");

    // initialize data
    field = new Field(fieldWidth, fieldHeight, fieldColor, bodyRadius, headRadius, userInitLine);
    board = new StatusBoard(boardX, boardY, windowWidth, windowHeight);

    // create 10 snowMans
    for (int i = 0; i < 10; i++) {
        field->createSnowMan();
    }

    glutReshapeFunc(resizeScene);
    glutDisplayFunc(renderScene);
    glutIdleFunc(handleMovement);

    // add keyboard functions
    glutSpecialFunc(pressKey);

    glutIgnoreKeyRepeat(1);
    glutSpecialUpFunc(releaseKey);

    // OpenGL init
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return 0;
}


// functions

void renderScene() {

    // Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // reset transformation
    glLoadIdentity();

    field->render();

    board->setCollidedCount(field->getCollidedSnowManCount());

    board->render();

    glutSwapBuffers();
}

void resizeScene(int width, int height) {

    float ratio;

    windowWidth = width;
    windowHeight = height;

    if (windowHeight == 0) {
        windowHeight = 1;
    }

    ratio = windowWidth * 1.0f / windowHeight;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, windowWidth, windowHeight);

    // Set the correct perspective.
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

void pressKey(int key, int xx, int yy) {

    switch (key) {
        case GLUT_KEY_LEFT:
            deltaMove = -0.1f;
            break;

        case GLUT_KEY_RIGHT:
            deltaMove = 0.1f;
            break;

        default:
            return;
    }

}

void releaseKey(int key, int xx, int yy) {

    switch (key) {
        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT:
            deltaMove = 0;
            break;
    }
}

void handleMovement() {

    if (deltaMove) {
        field->moveUser(deltaMove);
    }

    // creating new snowMan if 1 second has passed from last snowMan creation
    long time = glutGet(GLUT_ELAPSED_TIME);

    if (time > (elapsedSecond * 1000)) {
        elapsedSecond++;
        field->createSnowMan();
    }

    field->moveSnowMans(snowManMovementDistance);

    glutPostRedisplay();
}