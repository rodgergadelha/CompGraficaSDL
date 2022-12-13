#ifndef COMPLEX_OBJECT_H
#define COMPLEX_OBJECT_H

#include "vec3.h"
#include "matrix.h"
#include "object.h"
#include <vector>
#include <iostream>

class ComplexObject : public Object {
public:
    std::vector<Object*> components;
    Object *intersectedComponent;

    double intersection(Vec3 observer, Vec3 d) override {
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

    virtual void transform(Matrix m, bool rotateAxis = true) override {
        for(auto component : components) {
            component->transform(m);
        }

        this->center = components[0]->center;
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
};

#endif