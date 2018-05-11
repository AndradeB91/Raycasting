#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <libs/glm/glm/glm.hpp>

class Triangle
{
public:
    Triangle();
    Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, float shininess);

    glm::vec3 getP1();
    glm::vec3 getP2();
    glm::vec3 getP3();

    glm::vec3 getNormal();

    glm::vec3 getKa();
    glm::vec3 getKd();
    glm::vec3 getKs();
    float getShininess();

private:
    glm::vec3 p1,p2,p3;
    glm::vec3 normal;

    //material related
    glm::vec3 ka;
    glm::vec3 kd;
    glm::vec3 ks;
    float shininess;
};

#endif // TRIANGLE_H
