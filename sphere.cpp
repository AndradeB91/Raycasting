#include "sphere.h"

Sphere::Sphere(){}

Sphere::Sphere(glm::vec3 center, float radius, glm::vec3 Ka, glm::vec3 Kd, glm::vec3 Ks, float shininess){
    this->center = center;
    this->radius = radius;
    this->Ka = Ka;
    this->Kd = Kd;
    this->Ks = Ks;
    this->shininess = shininess;
}

glm::vec3 Sphere::getCenter(){
    return this->center;
}

float Sphere::getRadius(){
    return this->radius;
}

glm::vec3 Sphere::getKa(){
    return this->Ka;
}

glm::vec3 Sphere::getKd(){
    return this->Kd;
}

glm::vec3 Sphere::getKs(){
    return this->Ks;
}

float Sphere::getShininess(){
    return this->shininess;
}
