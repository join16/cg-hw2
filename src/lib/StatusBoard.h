#ifndef CG_HW2_STATUSBOARD_H
#define CG_HW2_STATUSBOARD_H

#include <string>
#include <iostream>

#include "RGBColor.h"

using namespace std;

class StatusBoard {

public:
    StatusBoard(float _x, float _y, int _windowWidth, int _windowHeight);

    void render(RGBColor textColor, string str);

private:
    float x, y;
    int windowWidth, windowHeight;

    void setOrthographicProjection();
    void restorePerspectiveProjection();
    void renderBitmapString(void *font, string str);
};


#endif //CG_HW2_STATUSBOARD_H
