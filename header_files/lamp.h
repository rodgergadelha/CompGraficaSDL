#ifndef LAMP_H
#define LAMP_H

#include "vec3.h"
#include "matrix.h"
#include "object.h"
#include "cone.h"
#include "cilinder.h"
#include "sphere.h"
#include "spot_light.h"
#include "world.h"
#include <vector>
#include <iostream>

class Lamp : public Object {
public:
    Vec3 normal;
    Cone *head;
    SpotLight *light;
    Cilinder *stem1, *stem2, *base;
    Sphere *stem_base, *head_base;
    Object *intersectedComponent;

    Lamp(Vec3 center, World *world, double height, double baseRadius, double headRadius) {
        this->type = "lamp";
        this->kd.setCoordinates(0.9, 0.9, 0.9);
        this->ke.setCoordinates(0.6, 0.6, 0.6);
        this->ka.setCoordinates(0.8, 0.8, 0.8);
        this->shininess = 10;

        this->base = new Cilinder();
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


        this->stem1 = new Cilinder();
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

        this->stem_base = new Sphere();
        stem_base->radius = 1.25;
        stem_base->center.setCoordinates(stem1->topPlane.pPi.x, stem1->topPlane.pPi.y + stem_base->radius, stem1->topPlane.pPi.z);
        stem_base->color.setCoordinates(65, 65, 65);
        stem_base->kd = this->kd;
        stem_base->ke = this->ke;
        stem_base->ka = this->ka;
        stem_base->shininess = this->shininess;

        this->stem2 = new Cilinder();
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

        this->head_base = new Sphere();
        head_base->radius = 1.25;
        head_base->center.setCoordinates(stem2->topPlane.pPi.x, stem2->topPlane.pPi.y + head_base->radius, stem2->topPlane.pPi.z);
        head_base->color.setCoordinates(65, 65, 65);
        head_base->kd = this->kd;
        head_base->ke = this->ke;
        head_base->ka = this->ka;
        head_base->shininess = this->shininess;
        
        this->head = new Cone(false);
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

        this->light = new SpotLight(head_base->center, headCenter, 5, 25);
        light->intensity.setCoordinates(0.7, 0.7, 0.7);
        world->lights.push_back(this->light);
    }

    double intersection(Vec3 observer, Vec3 d) {
        std::vector<Object*> components {head, stem1, stem2, base, stem_base, head_base};
        double closestT = std::numeric_limits<double>::infinity();

        for(auto component : components) {
            double t = component->intersection(observer, d);
            
            if(t > 0 && t < closestT) {
                closestT = t;
                this->intersectedComponent = component;
            }
        }

        return closestT;
    }

    Vec3 getColor(Vec3 intersectionPoint) override {
        return intersectedComponent->getColor(intersectionPoint);
    }

    Vec3 getNormal(Vec3 intersectionPoint, Vec3 d) override {
        return intersectedComponent->getNormal(intersectionPoint, d);
    }

    void transform(Matrix m, bool rotateAxis = true) override {
        head->transform(m);
        light->transform(m);
        stem1->transform(m);
        stem2->transform(m);
        base->transform(m);
        stem_base->transform(m);
        head_base->transform(m);
    }


    bool checkShadow(Vec3 position, Light* light, std::vector<Object*> objects) override {
        double closestTShadow = std::numeric_limits<double>::infinity();
        Object* closestObjectShadow = nullptr;
        Vec3 pf_sub_pi = light->getL(position);
        Vec3 l = pf_sub_pi / pf_sub_pi.getLength();
        Object *oldIntersectedComponent;
        
        for(auto object : objects) {
            oldIntersectedComponent = &(*intersectedComponent);
            double t = object->intersection(position, l);
            this->intersectedComponent = &(*oldIntersectedComponent);

            if(object == this || t <= 0.001 || object->type == "plane") continue;

            if(t < closestTShadow && (t < pf_sub_pi.getLength() || light->getType() == "directional")) {
                closestTShadow = t;
                closestObjectShadow = object;
            }
        }

        return closestObjectShadow != nullptr;
    }

    void setK(Vec3 k, std::string k_type) override {
        std::vector<Object*> components {head, stem1, stem2, base, stem_base, head_base};
        for(auto component : components) {
            component->setK(k, k_type);
        }
    }
    
};

#endif