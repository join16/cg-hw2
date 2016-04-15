#ifndef CG_HW2_SNOWMAN_H
#define CG_HW2_SNOWMAN_H

#include "Object.h"
#include "Vector.h"
#include "RGBColor.h"

class SnowMan : public Object {

public:
    SnowMan(float _bodyRadius, float _headRadius);
    SnowMan(Vector _core, float _bodyRadius, float _headRadius, Vector _direction);
    ~SnowMan();

    void render();
    void moveToDirection(float distance);

    void reset(Vector _core, Vector _direction);

    bool isLesserThanMaxX(float maxX);

    bool isEnabled();

    void enable();
    void disable();

private:
    Vector *direction;

    bool enabled = false;

    void renderBody();
    void renderHead();
    void renderEyes();
    void renderNose();

};

#endif //CG_HW2_SNOWMAN_H
