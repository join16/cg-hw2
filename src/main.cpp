
#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <string>

// include custom libs
#include "lib/Field.h"
#include "lib/StatusBoard.h"

using namespace std;

int window;

int windowWidth(640), windowHeight(640);
int windowPositionX(100), windowPositionY(100);

// snowMan movement distance
float snowManVelocity = 0.2f;
float userVelocity = 0.3;

float fieldWidth(100.0f), fieldHeight(100.0f);

// z coordinate of initial user position
float userInitLine = 5.0f;

float bodyRadius(0.75f), headRadius(0.25f);

// user movement along x, y axis
float deltaLeft(0), deltaRight(0), deltaUp(0), deltaDown(0);

// ms to call handleMovement function
unsigned int msToMove(10);

// ms to create new snowMan
unsigned int msToCreateSnowMan(300), msToCreateSuperSnowMan(3000);

bool paused = false;

// field
Field *field;
RGBColor fieldColor(0.9f, 0.9f, 0.9f);

// collision board
StatusBoard *collisionBoard;
RGBColor collisionTextColor(1.0f, 0.4f, 0.6f);
int collisionBoardX(30), collisionBoardY(50);
string collisionText = "Collided: ";

StatusBoard *centerBoard;
RGBColor pausedTextColor(0.0f, 0.6f, 1.0f);
string pausedText = "Pause (space: resume,  q: Exit)";
int centerBoardX(175), centerBoardY(250);

// function declarations
void renderScene();
void resizeScene(int width, int height);
void pressKey(int key, int xx, int yy);
void releaseKey(int key, int xx, int yy);
void handleMovement(int ms);

// main
int main(int argc, char *argv[]) {

    // for rand function
    srand((unsigned int) time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    // initialize window
    glutInitWindowPosition(windowPositionX, windowPositionY);
    glutInitWindowSize(windowWidth, windowHeight);
    window = glutCreateWindow("Snow Hunter");

    // initialize data
    field = new Field(fieldWidth, fieldHeight, fieldColor, bodyRadius, headRadius, userInitLine);
    collisionBoard = new StatusBoard(collisionBoardX, collisionBoardY, windowWidth, windowHeight);
    centerBoard = new StatusBoard(centerBoardX, centerBoardY, windowWidth, windowHeight);

    glutReshapeFunc(resizeScene);
    glutDisplayFunc(renderScene);
    glutTimerFunc(msToMove, handleMovement, 0);

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

    if (paused) {
        centerBoard->render(pausedTextColor, pausedText);
    }

    field->render();

    int collidedCount = field->getCollidedSnowManCount();

    collisionBoard->render(collisionTextColor, collisionText + to_string(collidedCount));

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
            deltaLeft = userVelocity;
            deltaRight = 0.0f;
            break;

        case GLUT_KEY_RIGHT:
            deltaLeft = 0.0f;
            deltaRight = userVelocity;
            break;

        case GLUT_KEY_UP:
            deltaUp = 0.1f;
            deltaDown = 0.0f;
            break;

        case GLUT_KEY_DOWN:
            deltaUp = 0.0f;
            deltaDown = 0.1f;
            break;

        case ' ':
            paused = !paused;

            // to display "Paused" text
            glutPostRedisplay();
            break;

        case 'q':
            glutDestroyWindow(window);
            exit(0);

        default:
            return;
    }

}

void releaseKey(int key, int xx, int yy) {

    switch (key) {
        case GLUT_KEY_LEFT:
            deltaLeft = 0;
            break;

        case GLUT_KEY_RIGHT:
            deltaRight = 0;
            break;

        case GLUT_KEY_UP:
            deltaUp = 0;
            break;

        case GLUT_KEY_DOWN:
            deltaDown = 0;
            break;

        default:
            return;
    }
}

void handleMovement(int ms) {

    glutTimerFunc(msToMove, handleMovement, ms + msToMove);

    // is paused, no action
    if (paused) {
        return;
    }

    if (-deltaLeft + deltaRight) {
        field->moveUser(-deltaLeft + deltaRight);
    }

    if (-deltaDown + deltaUp) {
        field->moveCameraVertically(-deltaDown + deltaUp);
    }

    // create snowMan for every msToCreateSnowMan
    if (ms % msToCreateSnowMan == 0) {
        bool isSuperSnowMan = ms % msToCreateSuperSnowMan == 0;

        field->createSnowMan(snowManVelocity, isSuperSnowMan);
    }

    field->moveSnowMans();

    glutPostRedisplay();
}