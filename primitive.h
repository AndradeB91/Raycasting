#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#define SPHERE 0
#define TRIANGLE 1

#include "sphere.h"
#include "triangle.h"

class Primitive
{
public:
    Primitive();
    Primitive(Sphere sphere);
    Primitive(Triangle triangle);

    int getType();
    Sphere getSphere();
    Triangle getTriangle();

private:
    Sphere sphere;
    Triangle triangle;
    int type;

};

#endif // PRIMITIVE_H
