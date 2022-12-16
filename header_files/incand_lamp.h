#ifndef INCAND_LAMP_H
#define INCAND_LAMP_H

#include "vec3.h"
#include "matrix.h"
#include "complex_object.h"
#include "cone.h"
#include "cilinder.h"
#include "sphere.h"
#include "point_light.h"
#include "world.h"
#include <vector>
#include <iostream>

class IncandLamp : public ComplexObject {
public:
    PointLight *light;
   
    IncandLamp(Vec3 center, World *world, double radius, double baseRadius, double baseHeight) {
        this->type = "incandescent lamp";
        this->kd.setCoordinates(0.5, 0.5, 0.5);
        this->ke.setCoordinates(0.6, 0.6, 0.6);
        this->ka.setCoordinates(0.7, 0.7, 0.7);
        this->shininess = 10;
        this->center = center;

        Cilinder *base = new Cilinder();
        base->center.setCoordinates(center.x, center.y, center.z);
        base->height = baseHeight;
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
        
        Sphere *lamp = new Sphere();
        lamp->radius = radius;
        lamp->center.setCoordinates(base->center.x, base->center.y - radius, base->center.z);
        lamp->color.setCoordinates(255, 255, 255);
        lamp->kd = Vec3(1, 1, 1);
        lamp->ke = Vec3(0, 0, 0);
        lamp->ka = Vec3(1, 1, 1);
        lamp->shininess = 10;

        this->light = new PointLight();
        light->position.setCoordinates(lamp->center.x, lamp->center.y - radius, lamp->center.z);
        light->intensity.setCoordinates(0.7, 0.7, 0.7);
        world->complex_objects_lights.push_back(this->light);

        this->components = std::vector<Object*> {base, lamp};

        cluster = new Sphere();
        cluster->center.setCoordinates(this->center.x, this->center.y, this->center.z);
        cluster->radius = (baseHeight + radius*2);
    }

    void transform(Matrix m, bool rotateAxis = true) override {
        for(auto component : components) {
            component->transform(m);
        }

        light->transform(m);
        
        this->center = components[0]->center;
        cluster->transform(m);
    }
    
};

#endif