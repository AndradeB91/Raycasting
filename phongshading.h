#ifndef PHONGSHADING_H
#define PHONGSHADING_H

#include <iostream>
#include <math.h>
#include <libs/glm/glm/glm.hpp>

#include "sphere.h"
#include "triangle.h"
#include "light.h"
#include "camera.h"

class PhongShading
{
public:
    PhongShading();
    glm::vec3 calculatePhongReflectionOnASphere(glm::vec3 intersectionPoint, Sphere sphere, Light light, Camera cam);
    glm::vec3 calculatePhongReflectionOnATriangle(glm::vec3 intersectionPoint, Triangle triangle, Light light, Camera cam);

private:

};

#endif // PHONGSHADING_H
