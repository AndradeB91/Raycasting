#include "primitive.h"


Primitive::Primitive(){}

Primitive::Primitive(Sphere sphere)
{
    this->sphere = sphere;
    this->type = SPHERE;
}

Primitive::Primitive(Triangle triangle)
{
    this->triangle = triangle;
    this->type = TRIANGLE;
}

int Primitive::getType(){
    return this->type;
}

Sphere Primitive::getSphere(){
    return this->sphere;
}

Triangle Primitive::getTriangle(){
    return this->triangle;
}
