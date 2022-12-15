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
    Sphere *cluster;

    double intersection(Vec3 observer, Vec3 d) override {
        if(cluster->intersection(observer, d) == -1) return -1;

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
        cluster->transform(m);
    }

    Vec3 getK(std::string type) override {
        return intersectedComponent->getK(type);
    }
    
};

#endif