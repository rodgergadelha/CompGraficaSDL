#ifndef TABLE_H
#define TABLE_H

#include "vec3.h"
#include "matrix.h"
#include "cube.h"
#include <vector>
#include <iostream>

class Table : public Object {
public:
    Vec3 normal;
    Cube *cover, *leg1, *leg2, *leg3, *leg4;
    Cube *intersectedComponent;
    double w, h;

    Table(Vec3 center, double w, double h) {
        this->w = w;
        this->h = h;
        this->type = "table";
        
        this->cover = new Cube(1, Vec3(0, 0, 0));
        cover->scale(w, 1, h);
        cover->translate(center.x, center.y, center.z);

        this->leg1 = new Cube(1, Vec3(0, 0, 0));
        leg1->scale(1, h, 1);
        leg1->translate(center.x + w/2 - 2, center.y - h/2, center.z - h/2 + 2);
        

        this->leg2 = new Cube(1, Vec3(0, 0, 0));
        leg2->scale(1, h, 1);
        leg2->translate(center.x - w/2 + 2, center.y - h/2, center.z - h/2 + 2);

        this->leg3 = new Cube(1, Vec3(0, 0, 0));
        leg3->scale(1, h, 1);
        leg3->translate(center.x + w/2 - 2, center.y - h/2, center.z + h/2 - 2);

        this->leg4 = new Cube(1, Vec3(0, 0, 0));
        leg4->scale(1, h, 1);
        leg4->translate(center.x - w/2 + 2, center.y - h/2, center.z + h/2 - 2);
    }

    double intersection(Vec3 observer, Vec3 d) {
        std::vector<Cube*> components {cover, leg1, leg2, leg3, leg4};
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

    void transform(Matrix m) override {
        cover->transform(m);
        leg1->transform(m);
        leg2->transform(m);
        leg3->transform(m);
        leg4->transform(m);
    }
    
};

#endif