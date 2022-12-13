#ifndef CLOSET_H
#define CLOSET_H

#include "vec3.h"
#include "matrix.h"
#include "object.h"
#include "cube.h"
#include "cilinder.h"
#include "world.h"
#include <vector>
#include <iostream>

class Closet : public Object {
public:
    Cube *closet;
    Cilinder *leg1, *leg2, *leg3, *leg4;
    Object *intersectedComponent;

    Closet(Vec3 center, Vec3 color, double width, double height, double depth, double legRadius, double legHeight) {
        this->type = "closet";
        this->kd.setCoordinates(0.9, 0.9, 0.9);
        this->ke.setCoordinates(0.6, 0.6, 0.6);
        this->ka.setCoordinates(0.8, 0.8, 0.8);
        this->shininess = 10;
        
        this->closet = new Cube(1, Vec3(0, 0, 0));
        closet->color = color;
        closet->scale(width, height, depth);
        closet->translate(center.x, center.y, center.z);

        this->leg1 = new Cilinder();
        this->leg2 = new Cilinder();
        this->leg3 = new Cilinder();
        this->leg4 = new Cilinder();
        
        leg1->center.setCoordinates(center.x + width/2 - 2, center.y - height/2 - legHeight, center.z - depth/2 + 2);
        leg2->center.setCoordinates(center.x - width/2 + 2, center.y - height/2 - legHeight, center.z - depth/2 + 2);
        leg3->center.setCoordinates(center.x + width/2 - 2, center.y - height/2 - legHeight, center.z + depth/2 - 2);
        leg4->center.setCoordinates(center.x - width/2 + 2, center.y - height/2 - legHeight, center.z + depth/2 - 2);
        
        std::vector<Cilinder*> legs {leg1, leg2, leg3, leg4};

        for(auto leg : legs) {
            leg->height = legHeight;
            leg->baseRadius = legRadius;
            leg->u.setCoordinates(0, 1, 0);
            leg->color.setCoordinates(color.x, color.y, color.z);
            leg->kd = this->kd;
            leg->ke = this->ke;
            leg->ka = this->ka;
            leg->shininess = this->shininess;
            leg->basePlane.pPi = leg->center*1;
            leg->basePlane.normal = leg->u*(-1);
            leg->topPlane.pPi = leg->center + (leg->u)*(leg->height);
            leg->topPlane.normal = (leg->u)*(leg->height);
        }
    }

    double intersection(Vec3 observer, Vec3 d) {
        std::vector<Object*> components {closet, leg1, leg2, leg3, leg4};
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
        closet->transform(m);
        leg1->transform(m);
        leg2->transform(m);
        leg3->transform(m);
        leg4->transform(m);
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
        std::vector<Object*> components {closet, leg1, leg2, leg3, leg4};
        for(auto component : components) {
            component->setK(k, k_type);
        }
    }
    
};

#endif