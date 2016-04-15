#ifndef CG_HW2_VECTOR_H
#define CG_HW2_VECTOR_H


class Vector {

public:
    Vector();
    Vector(const Vector &p);
    Vector(float _x, float _y, float _z);

    float getX() const;
    float getY() const;
    float getZ() const;

    void setX(float _x);
    void setY(float _y);
    void setZ(float _z);
    void set(float _x, float _y, float _z);
    void set(Vector p);

    void addX(float _x);
    void addY(float _y);
    void addZ(float _z);

    void normalize();

    void print();

    Vector operator+(Vector &p);
    Vector operator-(Vector &p);
    Vector operator*(float scale);

    float getSize();

    static float getDistance(Vector v1, Vector v2);

protected:
    float x, y, z;

};


#endif //CG_HW2_VECTOR_H
