#include <QApplication>
#include <QImage>
#include <QLabel>
#include <QList>

#include <stdio.h>
#include <iostream>
#include <time.h>

#include "primitive.h"
#include "ray.h"
#include "camera.h"
#include "light.h"
#include "twister.h"
#include "intersectionmanager.h"
#include "phongshading.h"

#include <libs/glm/glm/glm.hpp>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(a,b)  (((a) < (b)) ? (a) : (b))

const glm::vec2 SCREEN_SIZE(50,50);
const glm::vec3 BACKGROUND_COLOR(50,50,50);
QList<Primitive> models;
QList<Light> lights;

IntersectionManager intersecManager;
PhongShading phongController;
Twister twister;

Camera camera(glm::vec3(0,0,0),glm::vec3(0,0,-1));

void initializeLightProperties(){

    Light light(glm::vec3(0,0,-5));
    light.setIntensities(glm::vec3(1,1,1));
    light.setAttenuation(0.7);
    light.setAmbientColor(glm::vec3(0.1,0.1,0.1));
    light.setDiffuseColor(glm::vec3(0.8,0.8,0.8));
    light.setSpecularColor(glm::vec3(1,1,1));
    lights << light;

    Light light2(glm::vec3(-3,0.2,0));
    light2.setIntensities(glm::vec3(0.6,0.6,0.6));
    light2.setAttenuation(1);
    light2.setAmbientColor(glm::vec3(0.2,0.2,0.2));
    light2.setDiffuseColor(glm::vec3(0.8,0.8,0.8));
    light2.setSpecularColor(glm::vec3(1,1,1));
    //lights << light2;

}

void initializeObjects(){

    models << Sphere(glm::vec3(0,-3.5,-14) , 8, glm::vec3(0.2,0.2,0.2), glm::vec3(1,1,0), glm::vec3(1,1,1), 100);
    models << Sphere(glm::vec3(-3,5,-8) , 2, glm::vec3(0.2,0.2,0.2), glm::vec3(1,1,1), glm::vec3(1,1,1), 100);

    models << Sphere(glm::vec3(-1,0,-2) , 0.5, glm::vec3(0.2,0.2,0.2), glm::vec3(0,1,0), glm::vec3(1,1,1), 100);
    models << Sphere(glm::vec3(1,0,-3) , 0.5, glm::vec3(0.2,0.2,0.2), glm::vec3(0,0,1), glm::vec3(1,1,1), 100);
    models << Sphere(glm::vec3(0,-0.5,-3.5) , 0.7, glm::vec3(0.2,0.2,0.2), glm::vec3(1,0,0), glm::vec3(1,1,1), 100);

}

bool isPixelInShadow(Ray ray, int index){
    float res;
    for(int i = 0; i<models.size(); i++){
        if(i!=index){
            switch(models[i].getType()){
            case SPHERE:
                res = intersecManager.getRaySphereIntersection(ray,models[i].getSphere());
                break;
            case TRIANGLE:
                res = intersecManager.getRayTriangleIntersection(ray,models[i].getTriangle());
                break;
            }

            //res = intersecManager.getRaySphereIntersection(ray,models.at(i));
            if(res >= 0) return true;
        }
    }
    return false;
}

float checkPercentageOfLight(glm::vec3 intersectionPoint, int index, Light light){

    float retVal = 0;
    glm::vec3 stochasticVector = light.getPosition();
    glm::vec3 L = light.getPosition();

    float randFactor = (rand()%10000)*((float)1/(100000));
    int it = 4;
    int div = 5;
    int SAMPLES = (it*2+1)*(it*2+1);


    for(int i = -it; i <= it; i++){
        for(int j = -it; j <= it; j++){

            stochasticVector.x = L.x + (float)i/div + randFactor;
            stochasticVector.z = L.z + (float)j/div + randFactor;

            Ray shadowRay(intersectionPoint,stochasticVector);
            if(!isPixelInShadow(shadowRay,index)){
                retVal += (float)1/SAMPLES;
            }
        }
    }
    return retVal;

}

int findClosestIntersection(Ray ray, float &closestIntersection, int primitiveIndex){

    closestIntersection = INT_MAX;
    float intersection = 0;
    float index = -1;

    for(int i = 0; i<models.size(); i++){
        if(i != primitiveIndex){

            switch(models[i].getType()){
            case SPHERE:
                intersection = intersecManager.getRaySphereIntersection(ray,models[i].getSphere());
                break;
            case TRIANGLE:
                intersection = intersecManager.getRayTriangleIntersection(ray,models[i].getTriangle());
                break;
            }

            if(intersection < closestIntersection && intersection != -1 && intersection > 0.0){
                closestIntersection = intersection;
                index = i;
            }
        }
    }
    return index;
}

glm::vec3 raytracing(Ray ray, int &index, int primitiveIndex, float &closestIntersection){

    index = findClosestIntersection(ray,closestIntersection, primitiveIndex);

    if(index == -1){ //ray didn't find any object
        return BACKGROUND_COLOR;
    }

    //ray found an object and we start calculating colors + shadows
    else{
        //this is the intersection point
        glm::vec3 pointHitted = ray.getPO() + closestIntersection*ray.getDirection();

        //from 0 to 1 (1 being 100% light and 0 being all shadowed)
        float percentageOfLight = checkPercentageOfLight(pointHitted, index, lights[0]);

        for(int i = 0; i<lights.size(); i++){
            percentageOfLight += checkPercentageOfLight(pointHitted, index, lights[i]);
        }
        percentageOfLight /= lights.size();
        percentageOfLight = MIN(percentageOfLight, 1);

        percentageOfLight -= (float)(1-percentageOfLight)/10;
        percentageOfLight = MAX(percentageOfLight,0);

        glm::vec3 finalColor = glm::vec3(0,0,0);
        if(models[index].getType() == SPHERE){
            for(int i = 0; i<lights.size(); i++){
                finalColor += phongController.calculatePhongReflectionOnASphere(pointHitted,models[index].getSphere(),lights[i],camera);
            }
        }
        else {
            for(int i = 0; i<lights.size(); i++){
                finalColor += phongController.calculatePhongReflectionOnATriangle(pointHitted,models[index].getTriangle(),lights[i],camera);
            }
        }
        finalColor.x = MIN(finalColor.x,1);
        finalColor.y = MIN(finalColor.y,1);
        finalColor.z = MIN(finalColor.z,1);

        return glm::vec3(255*finalColor.x*percentageOfLight, 255*finalColor.y*percentageOfLight, 255*finalColor.z*percentageOfLight);

    }
}

glm::vec3 findReflectionVector(glm::vec3 intersectionPoint, int index){
    glm::vec3 normalVec;
    switch(models[index].getType()){
        case SPHERE:
            normalVec = glm::normalize(intersectionPoint - models[index].getSphere().getCenter());
            break;
        case TRIANGLE:
            normalVec = models[index].getTriangle().getNormal();
            break;
    }

    glm::vec3 incidentVec = glm::normalize(intersectionPoint);
    glm::vec3 reflection = incidentVec - (2*glm::dot(incidentVec,normalVec))*normalVec;
    return reflection;
}

glm::vec3 calculateDiffuseReflection(Ray ray, int &index2, int index, float closestIntersection ){
    glm::vec3 RP = ray.getDirection();

    glm::vec3 RN1 = glm::vec3(RP.z,RP.y,-RP.x);
    glm::vec3 RN2 = glm::cross(RP,RN1);
    float drefl = 0.3;
    int SAMPLES = 128;
    float randFactor;

    glm::vec3 mixedColors = glm::vec3(0,0,0);

    for(int i = 0; i < SAMPLES; i++){
        float xoffs, yoffs;

        xoffs = twister.Rand() * drefl;
        yoffs = twister.Rand() * drefl;

        glm::vec3 R = RP + RN1*xoffs + RN2*xoffs*drefl;
        R = glm::normalize(R);

        Ray modifiedRay(ray.getPO(),(R+ray.getPO()));
        mixedColors += raytracing(modifiedRay,index2,index,closestIntersection);
    }
    mixedColors.x /= SAMPLES;
    mixedColors.y /= SAMPLES;
    mixedColors.z /= SAMPLES;

    return mixedColors;
}

void Render(QImage &image){

    initializeLightProperties();
    initializeObjects();

    float stepX = 2/SCREEN_SIZE.x;
    float stepY = 2/SCREEN_SIZE.y;

    glm::vec3 firstPixel(-1,1,-1);
    glm::vec3 currentPixel;
    currentPixel.z = firstPixel.z;

    int index;
    float closestIntersection;

    for(int j = 0; j<SCREEN_SIZE.y; j++){
        for(int i = 0; i<SCREEN_SIZE.x; i++){

            currentPixel.x = i*stepX+firstPixel.x; //goes from -1 to 1
            currentPixel.y = firstPixel.y-j*stepY; //goes from 1 to -1

            Ray ray(camera.getPosition(),currentPixel);
            glm::vec3 color = raytracing(ray,index,-1,closestIntersection);
            image.setPixel(i,j,qRgb(color.x,color.y,color.z));


            //if index is different than -1 the ray has found some object
            if(index != -1){
                glm::vec3 hitPoint = ray.getPO() + closestIntersection*ray.getDirection();
                glm::vec3 reflectionVec = findReflectionVector(hitPoint,index);
                Ray ray2(hitPoint ,(reflectionVec + hitPoint));

                int index2;

                glm::vec3 color2 = raytracing(ray2,index2,index,closestIntersection);

                if(index2 == -1){
                    image.setPixel(i,j,qRgb(color.x,color.y,color.z));
                }else{
                    float fc1 = (float)3/4;
                    float fc2 = (float)1/4;
                    image.setPixel(i,j,qRgb(fc1*color.x + fc2*color2.x, fc1*color.y + fc2*color2.y, fc1*color.z + fc2*color2.z));
                }

            }else{
                image.setPixel(i,j,qRgb(color.x,color.y,color.z));
            }
        }
    }

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QImage image(SCREEN_SIZE.x,SCREEN_SIZE.y, QImage::Format_RGB32);
    QLabel myLabel;

    Render(image);

    myLabel.setPixmap(QPixmap::fromImage(image,Qt::AutoColor));
    myLabel.show();

    return a.exec();
}
