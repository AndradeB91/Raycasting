#include "light.h"

Light::Light(glm::vec3 position)
{
    this->position = position;
}

glm::vec3 Light::getPosition(){
    return this->position;
}

glm::vec3 Light::getIntensities(){
    return this->intensities;
}

float Light::getAttenuation(){
    return this->attenuation;
}

glm::vec3 Light::getAmbientColor(){
    return this->ambientColor;
}

glm::vec3 Light::getDiffuseColor(){
    return this->diffuseColor;
}

glm::vec3 Light::getSpecularColor(){
    return this->specularColor;
}

void Light::setPosition(glm::vec3 position){
    this->position = position;
}

void Light::setIntensities(glm::vec3 intensities){
    this->intensities = intensities;
}

void Light::setAttenuation(float attenuation){
    this->attenuation = attenuation;
}

void Light::setAmbientColor(glm::vec3 ambientColor){
    this->ambientColor = ambientColor;
}

void Light::setDiffuseColor(glm::vec3 diffuseColor){
    this->diffuseColor = diffuseColor;
}

void Light::setSpecularColor(glm::vec3 specularColor){
    this->specularColor = specularColor;
}
