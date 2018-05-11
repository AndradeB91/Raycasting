#include "triangle.h"

Triangle::Triangle(){}

Triangle::Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, float shininess){
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;

    this->ka = ka;
    this->kd = kd;
    this->ks = ks;
    this->shininess = shininess;

    glm::vec3 p1p2 = p2 - p1;
    glm::vec3 p1p3 = p3 - p1;
    this->normal = glm::normalize(glm::cross(p1p2,p1p3));
}

glm::vec3 Triangle::getP1(){
    return this->p1;
}

glm::vec3 Triangle::getP2(){
    return this->p2;
}

glm::vec3 Triangle::getP3(){
    return this->p3;
}

glm::vec3 Triangle::getKa(){
    return this->ka;
}

glm::vec3 Triangle::getKd(){
    return this->kd;
}

glm::vec3 Triangle::getKs(){
    return this->ks;
}

float Triangle::getShininess(){
    return this->shininess;
}

glm::vec3 Triangle::getNormal(){
    return this->normal;
}

