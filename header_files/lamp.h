#ifndef LAMP_H
#define LAMP_H

#include "vec3.h"
#include "matrix.h"
#include "complex_object.h"
#include "cone.h"
#include "cilinder.h"
#include "sphere.h"
#include "spot_light.h"
#include "world.h"
#include <vector>
#include <iostream>

class Lamp : public ComplexObject {
public:
    SpotLight *light;
   
    Lamp(Vec3 center, World *world, double height, double baseRadius, double headRadius) {
        this->type = "lamp";
        this->kd.setCoordinates(0.9, 0.9, 0.9);
        this->ke.setCoordinates(0.6, 0.6, 0.6);
        this->ka.setCoordinates(0.8, 0.8, 0.8);
        this->shininess = 10;
        this->center = center;

        Cilinder *base = new Cilinder();
        base->center.setCoordinates(center.x, center.y, center.z);
        base->height = 1;
        base->baseRadius = baseRadius;
        base->u.setCoordinates(0, 1, 0);
        base->color.setCoordinates(65, 65, 65);
        base->kd = this->kd;
        base->ke = this->ke;
        base->ka = this->ka;
        base->shininess = this->shininess;
        base->basePlane.pPi = base->center*1;
        base->basePlane.normal = base->u*(-1);
        base->topPlane.pPi = base->center + (base->u)*(base->height);
        base->topPlane.normal = (base->u)*(base->height);


        Cilinder *stem1 = new Cilinder();
        stem1->center.setCoordinates(base->center.x, base->center.y + 1, base->center.z);
        stem1->height = height/2;
        stem1->baseRadius = 0.85;
        stem1->u.setCoordinates(0, 1, 0);
        stem1->color.setCoordinates(192, 194, 192);
        stem1->kd = this->kd;
        stem1->ke = this->ke;
        stem1->ka = this->ka;
        stem1->shininess = this->shininess;
        stem1->basePlane.pPi = stem1->center*1;
        stem1->basePlane.normal = stem1->u*(-1);
        stem1->topPlane.pPi = stem1->center + (stem1->u)*(stem1->height);
        stem1->topPlane.normal = (stem1->u)*(stem1->height);

        Sphere *stem_base = new Sphere();
        stem_base->radius = 1.25;
        stem_base->center.setCoordinates(stem1->topPlane.pPi.x, stem1->topPlane.pPi.y + stem_base->radius, stem1->topPlane.pPi.z);
        stem_base->color.setCoordinates(65, 65, 65);
        stem_base->kd = this->kd;
        stem_base->ke = this->ke;
        stem_base->ka = this->ka;
        stem_base->shininess = this->shininess;

        Cilinder *stem2 = new Cilinder();
        stem2->center.setCoordinates(stem_base->center.x, stem_base->center.y + stem_base->radius, stem_base->center.z);
        stem2->height = height/2;
        stem2->baseRadius = 0.85;
        Vec3 axis(0, 1, 0.5);
        axis = axis / axis.getLength();
        stem2->u.setCoordinates(axis.x, axis.y, axis.z);
        stem2->color.setCoordinates(192, 194, 192);
        stem2->kd = this->kd;
        stem2->ke = this->ke;
        stem2->ka = this->ka;
        stem2->shininess = this->shininess;
        stem2->basePlane.pPi = stem2->center*1;
        stem2->basePlane.normal = stem2->u*(-1);
        stem2->topPlane.pPi = stem2->center + (stem2->u)*(stem2->height);
        stem2->topPlane.normal = (stem2->u)*(stem2->height);

        Sphere *head_base = new Sphere();
        head_base->radius = 1.25;
        head_base->center.setCoordinates(stem2->topPlane.pPi.x, stem2->topPlane.pPi.y + head_base->radius, stem2->topPlane.pPi.z);
        head_base->color.setCoordinates(65, 65, 65);
        head_base->kd = this->kd;
        head_base->ke = this->ke;
        head_base->ka = this->ka;
        head_base->shininess = this->shininess;
        
        Cone *head = new Cone(false);
        head->height = 5;
        head->baseRadius = headRadius;
        axis = Vec3(0, 1, -1);
        axis = axis / axis.getLength();
        Vec3 headCenter = head_base->center - (axis * head->height); 
        head->center.setCoordinates(headCenter.x, headCenter.y, headCenter.z);
        head->n.setCoordinates(axis.x, axis.y, axis.z);
        head->color.setCoordinates(192, 194, 192);
        head->kd = this->kd;
        head->ke = this->ke;
        head->ka = this->ka;
        head->shininess = this->shininess;

        this->light = new SpotLight(head->center * 1, Vec3(0, 0, 0), 5, 30);
        light->spotDirection = head->n * (-1);
        light->intensity.setCoordinates(0.7, 0.7, 0.7);
        world->lights.push_back(this->light);

        this->components = std::vector<Object*> {base, head, stem1, stem2, stem_base, head_base};
        
        cluster = new Sphere();
        cluster->center.setCoordinates(stem_base->center.x, stem_base->center.y, stem_base->center.z);
        cluster->radius = 1 + (2 * stem1->height) + stem_base->radius + head_base->radius;
    }

    void transform(Matrix m, bool rotateAxis = true) override {
        for(auto component : components) {
            component->transform(m);
        }
        
        light->transform(m);
        
        this->center.setCoordinates(components[0]->center.x, components[0]->center.y, components[0]->center.z);
        cluster->transform(m);
    }
    
};

#endif