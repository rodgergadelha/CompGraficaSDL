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
    Object *intersectedComponent;

    Table(Vec3 center, double cover_w, double cover_h, double leg_w, double leg_h, double leg_d) {
        this->type = "table";
        
        this->cover = new Cube(1, Vec3(0, 0, 0));
        cover->scale(cover_w, 1, cover_h);
        cover->translate(center.x, center.y, center.z);

        this->leg1 = new Cube(1, Vec3(0, 0, 0));
        leg1->scale(leg_w, leg_h, leg_d);
        leg1->translate(center.x + cover_w/2 - 2, center.y - leg_h/2, center.z - cover_h/2 + 2);

        this->leg2 = new Cube(1, Vec3(0, 0, 0));
        leg2->scale(leg_w, leg_h, leg_d);
        leg2->translate(center.x - cover_w/2 + 2, center.y - leg_h/2, center.z - cover_h/2 + 2);

        this->leg3 = new Cube(1, Vec3(0, 0, 0));
        leg3->scale(leg_w, leg_h, leg_d);
        leg3->translate(center.x + cover_w/2 - 2, center.y - leg_h/2, center.z + cover_h/2 - 2);

        this->leg4 = new Cube(1, Vec3(0, 0, 0));
        leg4->scale(leg_w, leg_h, leg_d);
        leg4->translate(center.x - cover_w/2 + 2, center.y - leg_h/2, center.z + cover_h/2 - 2);
    }

    double intersection(Vec3 observer, Vec3 d) {
        std::vector<Object*> components {cover, leg1, leg2, leg3, leg4};
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
        cover->transform(m);
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
        std::vector<Object*> components {cover, leg1, leg2, leg3, leg4};
        for(auto component : components) {
            component->setK(k, k_type);
        }
    }
    
};

#endif