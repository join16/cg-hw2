#ifndef CG_HW2_RGBCOLOR_H
#define CG_HW2_RGBCOLOR_H


class RGBColor {

public:

    // constructors
    RGBColor();
    RGBColor(const RGBColor &color);
    RGBColor(float _red, float _green, float _blue);

    void print();
    void set(RGBColor color);
    float getR() const;
    float getG() const;
    float getB() const;

    void setGlColor() const;

    static RGBColor getWhite();
    static RGBColor getBlack();

private:
    float red;
    float green;
    float blue;

};


#endif //CG_HW2_RGBCOLOR_H