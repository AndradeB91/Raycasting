#ifndef RAY_H
#define RAY_H

#include <libs/glm/glm/glm.hpp>

class Ray
{
public:
    Ray(glm::vec3 pO, glm::vec3 pF);

    glm::vec3 getPO();
    glm::vec3 getPF();
    glm::vec3 getDirection();

private:
    glm::vec3 pO;
    glm::vec3 pF;

};

#endif // RAY_H
