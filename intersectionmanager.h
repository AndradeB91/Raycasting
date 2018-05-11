#ifndef INTERSECTIONMANAGER_H
#define INTERSECTIONMANAGER_H

#include "sphere.h"
#include "triangle.h"
#include "ray.h"
#include <libs/glm/glm/glm.hpp>
#include <iostream>


class IntersectionManager
{
public:
    IntersectionManager();

    float getRaySphereIntersection(Ray ray, Sphere sphere);
    //bool getRayTriangleIntersection(Ray ray, Triangle tri, float &t);
    float getRayTriangleIntersection(Ray ray, Triangle tri);
};

#endif // INTERSECTIONMANAGER_H
