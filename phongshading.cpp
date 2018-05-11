#include "phongshading.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(a,b)  (((a) < (b)) ? (a) : (b))

PhongShading::PhongShading()
{
}

glm::vec3 PhongShading::calculatePhongReflectionOnASphere(glm::vec3 intersectionPoint, Sphere sphere, Light light, Camera cam){

    glm::vec3 Ka = sphere.getKa();          //ambient coefficient
    glm::vec3 Ac = light.getAmbientColor(); //ambient color

    glm::vec3 Kd = sphere.getKd();          //diffuse coefficient
    glm::vec3 Dc = light.getDiffuseColor(); //diffuse color

    glm::vec3 Ks = sphere.getKs();          //specular coefficient
    glm::vec3 Sc = light.getSpecularColor(); //specular color

    glm::vec3 Lx = light.getIntensities(); //light color

    float Att = light.getAttenuation();
    float shininess = sphere.getShininess();


    glm::vec3 normalVec = glm::normalize(intersectionPoint   - sphere.getCenter());
    glm::vec3 lightVec  = glm::normalize(light.getPosition() - intersectionPoint );
    glm::vec3 viewVec   = glm::normalize(cam.getPosition()   - intersectionPoint );

    float angleNL = MAX(glm::dot(normalVec,lightVec),0);

    float normalLightTest = glm::dot(normalVec,lightVec);
    float angleRV;

    //This condition is to not calculate specular contribution when dealing with reflections
    if(normalLightTest < 0)
        angleRV = 0.0;
    else{
        glm::vec3 reflection = glm::normalize((2*normalLightTest)*normalVec - lightVec);
        angleRV = MAX(glm::dot(reflection,viewVec),0);
        angleRV = glm::pow(angleRV,shininess);
    }

    float Ir = MIN(Ac.x*Ka.x + Att*Lx.x*(Kd.x*Dc.x*angleNL + Ks.x*Sc.x*angleRV),1);
    float Ig = MIN(Ac.y*Ka.y + Att*Lx.y*(Kd.y*Dc.y*angleNL + Ks.y*Sc.y*angleRV),1);
    float Ib = MIN(Ac.z*Ka.z + Att*Lx.z*(Kd.z*Dc.z*angleNL + Ks.z*Sc.z*angleRV),1);

    return glm::vec3(Ir,Ig,Ib);
}


glm::vec3 PhongShading::calculatePhongReflectionOnATriangle(glm::vec3 intersectionPoint, Triangle triangle, Light light, Camera cam){

    glm::vec3 Ka = triangle.getKa();          //ambient coefficient
    glm::vec3 Ac = light.getAmbientColor(); //ambient color

    glm::vec3 Kd = triangle.getKd();          //diffuse coefficient
    glm::vec3 Dc = light.getDiffuseColor(); //diffuse color

    glm::vec3 Ks = triangle.getKs();          //specular coefficient
    glm::vec3 Sc = light.getSpecularColor(); //specular color

    glm::vec3 Lx = light.getIntensities(); //light color

    float Att = light.getAttenuation();
    float shininess = triangle.getShininess();


    glm::vec3 normalVec = triangle.getNormal();
    glm::vec3 lightVec  = glm::normalize(light.getPosition() - intersectionPoint );
    glm::vec3 viewVec   = glm::normalize(cam.getPosition()   - intersectionPoint );

    float angleNL = MAX(glm::dot(normalVec,lightVec),0);

    float normalLightTest = glm::dot(normalVec,lightVec);
    float angleRV;

    //This condition is to not calculate specular contribution when dealing with reflections
    if(normalLightTest < 0)
        angleRV = 0.0;
    else{
        glm::vec3 reflection = glm::normalize((2*normalLightTest)*normalVec - lightVec);
        angleRV = MAX(glm::dot(reflection,viewVec),0);
        angleRV = glm::pow(angleRV,shininess);
    }

    float Ir = MIN(Ac.x*Ka.x + Att*Lx.x*(Kd.x*Dc.x*angleNL + Ks.x*Sc.x*angleRV),1);
    float Ig = MIN(Ac.y*Ka.y + Att*Lx.y*(Kd.y*Dc.y*angleNL + Ks.y*Sc.y*angleRV),1);
    float Ib = MIN(Ac.z*Ka.z + Att*Lx.z*(Kd.z*Dc.z*angleNL + Ks.z*Sc.z*angleRV),1);

    return glm::vec3(Ir,Ig,Ib);
}

