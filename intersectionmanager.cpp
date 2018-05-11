#include "intersectionmanager.h"

IntersectionManager::IntersectionManager()
{
}

float IntersectionManager::getRaySphereIntersection(Ray ray, Sphere sphere){
    float A = glm::dot((ray.getPF() - ray.getPO()),(ray.getPF() - ray.getPO()));
    float B = 2 * glm::dot((ray.getPF() - ray.getPO()), (ray.getPO() - sphere.getCenter()));
    float C = glm::dot(ray.getPO(), ray.getPO()) - 2*glm::dot(ray.getPO(),sphere.getCenter())
            + glm::dot(sphere.getCenter(), sphere.getCenter()) - sphere.getRadius()*sphere.getRadius();

    float delta = B*B - 4*A*C;

    if(delta <= 0)
        return -1;
    else{
        return (-B - glm::sqrt(delta))/(2*A);
    }
}


float IntersectionManager::getRayTriangleIntersection(Ray ray, Triangle tri){
    float kEpsilon = 0.000001;
    glm::vec3 N = tri.getNormal();

    // Step 1: finding P
    //check if ray and plane are parallel
    float NdotRayDirection = glm::dot(N,ray.getDirection());
    if (fabs(NdotRayDirection) < kEpsilon) // almost 0
        return -1; // they are parallel so they don't intersect !

    //compute the parameter D on equation
    float d = glm::dot(N,tri.getP1());

    //compute t
    float t;
    float den = glm::dot(N,ray.getDirection());
    t = glm::dot(N,ray.getPO()) + d;
    t /= den;

    // check if the triangle is in behind the ray
    if (t < 0) return -1; // the triangle is behind

    //compute the intersection point using t
    glm::vec3 P = ray.getPO() + t*ray.getDirection();

    // Step 2: inside-outside test
    glm::vec3 C; // vector perpendicular to triangle's plane

    //std::cout << N.x << "||" << N.y << "||"  << N.z << std::endl;

    //first edge
    glm::vec3 edge1 = tri.getP2() - tri.getP1();
    glm::vec3 vp1 = P - tri.getP1();
    C = glm::cross(edge1,vp1);
    if(glm::dot(N,C) < 0) return -1;

    //second edge
    glm::vec3 edge2 = tri.getP3() - tri.getP2();
    glm::vec3 vp2 = P - tri.getP2();
    C = glm::cross(edge2,vp2);
    if(glm::dot(N,C) < 0) return -1;

    //third edge
    glm::vec3 edge3 = tri.getP1() - tri.getP3();
    glm::vec3 vp3 = P - tri.getP3();
    C = glm::cross(edge3,vp3);

    if(glm::dot(N,C) < 0) return -1;

    return t; //the ray hits the triangle
}



//bool IntersectionManager::getRayTriangleIntersection(Ray ray, Triangle tri, float &t){
//    float kEpsilon = 0.000001;
//    glm::vec3 N = tri.getNormal();

//    // Step 1: finding P
//    //check if ray and plane are parallel
//    float NdotRayDirection = glm::dot(N,ray.getDirection());
//    if (fabs(NdotRayDirection) < kEpsilon) // almost 0
//        return false; // they are parallel so they don't intersect !

//    //compute the parameter D on equation
//    float d = glm::dot(N,tri.getP1());

//    //compute t
//    float den = glm::dot(N,ray.getDirection());
//    t = glm::dot(N,ray.getPO()) + d;
//    t /= den;

//    // check if the triangle is in behind the ray
//    if (t < 0) return false; // the triangle is behind

//    //compute the intersection point using t
//    glm::vec3 P = ray.getPO() + t*ray.getDirection();

//    // Step 2: inside-outside test
//    glm::vec3 C; // vector perpendicular to triangle's plane

//    //std::cout << N.x << "||" << N.y << "||"  << N.z << std::endl;

//    //first edge
//    glm::vec3 edge1 = tri.getP2() - tri.getP1();
//    glm::vec3 vp1 = P - tri.getP1();
//    C = glm::cross(edge1,vp1);
//    if(glm::dot(N,C) < 0) return false;

//    //second edge
//    glm::vec3 edge2 = tri.getP3() - tri.getP2();
//    glm::vec3 vp2 = P - tri.getP2();
//    C = glm::cross(edge2,vp2);
//    if(glm::dot(N,C) < 0) return false;

//    //third edge
//    glm::vec3 edge3 = tri.getP1() - tri.getP3();
//    glm::vec3 vp3 = P - tri.getP3();
//    C = glm::cross(edge3,vp3);

//    if(glm::dot(N,C) < 0) return false;

//    return true; //the ray hits the triangle
//}


























