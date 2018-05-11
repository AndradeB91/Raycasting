#ifndef CAMERA_H
#define CAMERA_H

#include <libs/glm/glm/glm.hpp>

class Camera
{
public:
    Camera(glm::vec3 position, glm::vec3 lookAt);

    glm::vec3 getUpVec();
    glm::vec3 getRightVec();
    glm::vec3 getViewVec();
    glm::vec3 getPosition();
    glm::vec3 getLookAt();


private:
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 view;

    glm::vec3 position;
    glm::vec3 lookAt;
};

#endif // CAMERA_H
