#ifndef JAR_H
#define JAR_H

#include "vec3.h"
#include "matrix.h"
#include "complex_object.h"
#include "cube.h"
#include "cilinder.h"
#include <vector>
#include <iostream>

class Jar : public ComplexObject {
public:

    Jar(Vec3 center, double jar_height, double jar_radius, double plant_radius, double trunk_height) {

        this->type = "jar";
        this->kd.setCoordinates(0.9, 0.9, 0.9);
        this->ke.setCoordinates(0.6, 0.6, 0.6);
        this->ka.setCoordinates(0.8, 0.8, 0.8);
        this->shininess = 10;
        this->center = center;

        Cilinder *jar = new Cilinder();
        jar->center.setCoordinates(center.x, center.y, center.z);
        jar->height = jar_height;
        jar->baseRadius = jar_radius;
        jar->u.setCoordinates(0, 1, 0);
        jar->color.setCoordinates(235, 53, 21);
        jar->kd = this->kd;
        jar->ke = this->ke;
        jar->ka = this->ka;
        jar->shininess = this->shininess;
        jar->basePlane.pPi = jar->center*1;
        jar->basePlane.normal = jar->u*(-1);
        jar->topPlane.pPi = jar->center + (jar->u)*(jar->height);
        jar->topPlane.normal = (jar->u)*(jar->height);

        Cilinder *jar_top = new Cilinder();
        jar_top->center.setCoordinates(jar->topPlane.pPi.x, jar->topPlane.pPi.y, jar->topPlane.pPi.z);
        jar_top->height = jar_height * 0.5;
        jar_top->baseRadius = jar_radius * 1.2;
        jar_top->u.setCoordinates(0, 1, 0);
        jar_top->color.setCoordinates(235, 53, 21);
        jar_top->kd = this->kd;
        jar_top->ke = this->ke;
        jar_top->ka = this->ka;
        jar_top->shininess = this->shininess;
        jar_top->basePlane.pPi = jar_top->center*1;
        jar_top->basePlane.normal = jar_top->u*(-1);
        jar_top->topPlane.pPi = jar_top->center + (jar_top->u)*(jar_top->height);
        jar_top->topPlane.normal = (jar_top->u)*(jar_top->height);

        Cilinder *soil = new Cilinder();
        soil->center.setCoordinates(jar_top->topPlane.pPi.x, jar_top->topPlane.pPi.y, jar_top->topPlane.pPi.z);
        soil->height = 0.1;
        soil->baseRadius = jar_top->baseRadius;
        soil->u.setCoordinates(0, 1, 0);
        soil->color.setCoordinates(48, 27, 16);
        soil->kd = this->kd;
        soil->ke = this->ke;
        soil->ka = this->ka;
        soil->shininess = this->shininess;
        soil->basePlane.pPi = soil->center*1;
        soil->basePlane.normal = soil->u*(-1);
        soil->topPlane.pPi = soil->center + (soil->u)*(soil->height);
        soil->topPlane.normal = (soil->u)*(soil->height);

        Cilinder *trunk = new Cilinder();
        trunk->center.setCoordinates(soil->topPlane.pPi.x, soil->topPlane.pPi.y, soil->topPlane.pPi.z);
        trunk->height = trunk_height;
        trunk->baseRadius = jar->baseRadius * 0.1;
        trunk->u.setCoordinates(0, 1, 0);
        trunk->color.setCoordinates(82, 45, 26);
        trunk->kd = this->kd;
        trunk->ke = this->ke;
        trunk->ka = this->ka;
        trunk->shininess = this->shininess;
        trunk->basePlane.pPi = trunk->center*1;
        trunk->basePlane.normal = trunk->u*(-1);
        trunk->topPlane.pPi = trunk->center + (trunk->u)*(trunk->height);
        trunk->topPlane.normal = (trunk->u)*(trunk->height);
        
        
        Sphere *plant1 = new Sphere();
        plant1->radius = plant_radius;
        plant1->center.setCoordinates(trunk->topPlane.pPi.x, trunk->topPlane.pPi.y + plant_radius/2, trunk->topPlane.pPi.z);
        plant1->color.setCoordinates(0, 128, 0);
        plant1->kd = this->kd;
        plant1->ke = this->ke;
        plant1->ka = this->ka;
        plant1->shininess = this->shininess;

        Sphere *plant2 = new Sphere();
        plant2->radius = plant_radius / 3;
        plant2->center.setCoordinates(trunk->topPlane.pPi.x, trunk->topPlane.pPi.y - trunk_height + plant2->radius, trunk->topPlane.pPi.z + plant2->radius/2);
        plant2->color.setCoordinates(0, 128, 0);
        plant2->kd = this->kd;
        plant2->ke = this->ke;
        plant2->ka = this->ka;
        plant2->shininess = this->shininess;
        
        Sphere *plant3 = new Sphere();
        plant3->radius = plant_radius / 2.5;
        plant3->center.setCoordinates(trunk->topPlane.pPi.x + plant3->radius, trunk->topPlane.pPi.y - trunk_height/2, trunk->topPlane.pPi.z);
        plant3->color.setCoordinates(0, 128, 0);
        plant3->kd = this->kd;
        plant3->ke = this->ke;
        plant3->ka = this->ka;
        plant3->shininess = this->shininess;


        this->components = std::vector<Object*> {jar, jar_top, soil, trunk, plant1, plant2, plant3};

        cluster = new Sphere();
        cluster->center.setCoordinates(this->center.x, this->center.y + jar_height + trunk_height/4, this->center.z);
        cluster->radius = (jar_height + plant_radius + trunk_height);
    }
    
};

#endif