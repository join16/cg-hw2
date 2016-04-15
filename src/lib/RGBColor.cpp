
#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>

#include "RGBColor.h"

//
// constructors
//

RGBColor::RGBColor() : red(0), green(0), blue(0) { }

RGBColor::RGBColor(const RGBColor &color)
    : red(color.getR()), green(color.getG()), blue(color.getB()) {}

RGBColor::RGBColor(float _red, float _green, float _blue)
    : red(_red), green(_green), blue(_blue) { }


//
// methods
//

float RGBColor::getR() const {
    return red;
}

float RGBColor::getG() const {
    return green;
}

float RGBColor::getB() const {
    return blue;
}

void RGBColor::print() {
    printf("Color: (%f, %f, %f)\n", red, green, blue);
}

void RGBColor::set(RGBColor color) {
    red = color.getR();
    green = color.getG();
    blue = color.getB();
}

void RGBColor::setGlColor() const {
    glColor3f(red, green, blue);
}

//
// static methods
//

RGBColor RGBColor::getWhite() {
    return RGBColor(1.0f, 1.0f, 1.0f);
}
RGBColor RGBColor::getBlack() {
    return RGBColor(0.0f, 0.0f, 0.0f);
}