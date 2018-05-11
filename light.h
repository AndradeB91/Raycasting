#ifndef LIGHT_H
#define LIGHT_H

#include <libs/glm/glm/glm.hpp>

class Light
{
public:
    Light(glm::vec3 position);

    glm::vec3 getPosition();
    glm::vec3 getIntensities();
    float getAttenuation();

    glm::vec3 getAmbientColor();
    glm::vec3 getDiffuseColor();
    glm::vec3 getSpecularColor();

    void setPosition(glm::vec3 position);
    void setIntensities(glm::vec3 intensities);
    void setAttenuation(float attenuation);
    void setAmbientColor(glm::vec3 ambientColor);
    void setDiffuseColor(glm::vec3 diffuseColor);
    void setSpecularColor(glm::vec3 specularColor);

private:
    glm::vec3 position;
    glm::vec3 intensities;

    glm::vec3 ambientColor;
    glm::vec3 diffuseColor;
    glm::vec3 specularColor;
    float attenuation;

};

#endif // LIGHT_H
