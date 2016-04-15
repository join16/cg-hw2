#ifndef CG_HW2_OBJECT_H
#define CG_HW2_OBJECT_H

#include "Vector.h"

// base class of SnowNam, User
class Object {

public:
    Object();
    Object(Vector _core, float _bodyRadius, float _headRadius);
    virtual ~Object();

    void setPosition(Vector _core);
    void move(Vector diff);

    Vector getCore() const;
    float getBodyRadius();
    bool isCollided(Object *object);

protected:
    Vector *core;
    float bodyRadius;
    float headRadius;

};


#endif //CG_HW2_OBJECT_H
