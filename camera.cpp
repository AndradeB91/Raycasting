#include "camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 lookAt)
{
    this->position = position;
    this->lookAt = lookAt;

    glm::vec3 view = lookAt - position;
    this->view = glm::normalize(view);

    glm::vec3 right = glm::cross(glm::vec3(0,1,0), this->view);
    this->right = glm::normalize(right);

    glm::vec3 up = glm::cross(this->view, this->right);
    this->up = glm::normalize(up);
}

glm::vec3 Camera::getUpVec(){
    return this->up;
}

glm::vec3 Camera::getRightVec(){
    return this->right;
}

glm::vec3 Camera::getViewVec(){
    return this->view;
}

glm::vec3 Camera::getPosition(){
    return this->position;
}

glm::vec3 Camera::getLookAt(){
    return this->lookAt;
}
