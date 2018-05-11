#ifndef SPHERE_H
#define SPHERE_H

#include <libs/glm/glm/glm.hpp>

class Sphere
{
public:
    Sphere();
    Sphere(glm::vec3 center, float radius, glm::vec3 Ka, glm::vec3 Kd, glm::vec3 Ks, float shininess);

    glm::vec3 getCenter();
    float getRadius();

    glm::vec3 getKa();
    glm::vec3 getKd();
    glm::vec3 getKs();
    float getShininess();
private:
    glm::vec3 center;
    float radius;

    //material related
    glm::vec3 Ka;
    glm::vec3 Kd;
    glm::vec3 Ks;
    float shininess;
};

#endif // SPHERE_H
