#ifndef CG_HW2_USER_H
#define CG_HW2_USER_H

#include "Object.h"
#include "Vector.h"

class User : public Object {

public:
    User(Vector _core, float _bodyRadius, float _headRadius);

    void setGlCamera();
    Vector getCameraPoint();

    bool isGreaterThanMinX(float maxX);
    bool isLesserThanMaxX(float maxX);

private:
    Vector *lookUp, *gaze;

};


#endif //CG_HW2_USER_H
