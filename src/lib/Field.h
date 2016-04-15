#ifndef CG_HW2_FIELD_H
#define CG_HW2_FIELD_H

#include "Vector.h"
#include "RGBColor.h"
#include "User.h"
#include "SnowMan.h"

using namespace std;

const int maxSnowManCount = 1000;

// works as snowMan controller
class Field {

public:
    Field(float _width,
          float _height,
          RGBColor _color,
          float _bodyRadius,
          float _headRadius,
          float _userInitLine // z coordinate of initial user position
    );
    ~Field();

    void render();
    void createSnowMan(float velocity, bool isSuperSnowMan);
    void moveUser(float deltaX);
    void moveCameraVertically(float height);

    void moveSnowMans();

    int getCollidedSnowManCount();

private:

    // for x coordinate
    float width;
    // for z coordinate
    float height;

    float bodyRadius;
    float headRadius;

    int collidedSnowManCount = 0;
    int lastEnabledSnowManIndex = -1;

    RGBColor *color;
    User *user;

    SnowMan *snowMans[maxSnowManCount];

    void enableNextSnowMan(Vector _core, Vector _direction, float _velocity, bool isSuperSnowMan);
    void renderField();
    void renderSnowMans();

};


#endif //CG_HW2_FIELD_H
