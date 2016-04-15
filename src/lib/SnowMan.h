#ifndef CG_HW2_SNOWMAN_H
#define CG_HW2_SNOWMAN_H

#include "Object.h"
#include "Vector.h"
#include "RGBColor.h"

class SnowMan : public Object {

public:

    SnowMan(float _bodyRadius, float _headRadius);

    ~SnowMan();

    void render();
    void moveToDirection();
    void changeDirection(Vector _direction);

    void reset(Vector _core, Vector _direction, float _velocity);
    void setVelocity(float _velocity);
    void setColor(RGBColor _color);
    float getMovedDistance();

    bool isLesserThanMaxX(float maxX);
    bool isEnabled();

    void enable();
    void disable();

private:
    Vector *direction;
    RGBColor *color;

    bool enabled = false;
    float velocity = 0.0f;
    float movedDistance = 0.0f;

    void renderBody();
    void renderHead();
    void renderEyes();
    void renderNose();

};

#endif //CG_HW2_SNOWMAN_H
