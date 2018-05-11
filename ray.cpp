#include "ray.h"

Ray::Ray(glm::vec3 pO, glm::vec3 pF)
{
    this->pO = pO;
    this->pF = pF;
}

glm::vec3 Ray::getPO(){
    return this->pO;
}

glm::vec3 Ray::getPF(){
    return this->pF;
}

glm::vec3 Ray::getDirection(){
    return glm::normalize(this->pF - this->pO);
}
