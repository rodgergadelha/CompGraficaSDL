#ifndef CHAIR_H
#define CHAIR_H

#include "vec3.h"
#include "matrix.h"
#include "cube.h"
#include "cilinder.h"
#include "object.h"
#include <vector>
#include <iostream>

class Chair : public Object {
public:
    Vec3 normal;
    Cube *seat, *backrest;
    Cilinder *seat_leg1, *seat_leg2, *seat_leg3, *seat_leg4, *backrest_leg1, *backrest_leg2;
    Object *intersectedComponent;

    Chair(Vec3 center, Vec3 color, double seat_w, double seat_h, double backrest_w, double backrest_h,
    double seat_leg_radius, double seat_leg_h, double backrest_leg_radius, double backrest_leg_h) {
        
        this->type = "chair";
        this->color = color;
        this->kd.setCoordinates(0.9, 0.9, 0.9);
        this->ke.setCoordinates(0.6, 0.6, 0.6);
        this->ka.setCoordinates(0.8, 0.8, 0.8);
        this->shininess = 10;
        
        this->seat = new Cube(1, Vec3(0, 0, 0));
        seat->scale(seat_w, 1, seat_h);
        seat->translate(center.x, center.y, center.z);
        seat->setAllFacesColors(color);

        this->backrest = new Cube(1, Vec3(0, 0, 0));
        backrest->scale(backrest_w, backrest_h, 3);
        backrest->translate(center.x, center.y + backrest_leg_h + backrest_h/2, center.z - seat_h/2 + 2);
        backrest->setAllFacesColors(color);

        this->seat_leg1 = new Cilinder();
        this->seat_leg2 = new Cilinder();
        this->seat_leg3 = new Cilinder();
        this->seat_leg4 = new Cilinder();
        this->backrest_leg1 = new Cilinder();
        this->backrest_leg2 = new Cilinder();
        
        seat_leg1->center.setCoordinates(center.x + seat_w/2 - 2, center.y - seat_leg_h, center.z - seat_h/2 + 2);
        seat_leg2->center.setCoordinates(center.x - seat_w/2 + 2, center.y - seat_leg_h, center.z - seat_h/2 + 2);
        seat_leg3->center.setCoordinates(center.x + seat_w/2 - 2, center.y - seat_leg_h, center.z + seat_h/2 - 2);
        seat_leg4->center.setCoordinates(center.x - seat_w/2 + 2, center.y - seat_leg_h, center.z + seat_h/2 - 2);
        backrest_leg1->center.setCoordinates(backrest->center.x + backrest_w/2 - 2, backrest->center.y - backrest_leg_h - backrest_h/2, backrest->center.z);
        backrest_leg2->center.setCoordinates(backrest->center.x - backrest_w/2 + 2, backrest->center.y - backrest_leg_h - backrest_h/2, backrest->center.z);

        std::vector<Cilinder*> legs {seat_leg1, seat_leg2, seat_leg3, seat_leg4, backrest_leg1, backrest_leg2};

        for(int i = 0; i < 6; i++) {
            Cilinder* leg = legs[i];

            if(i > 3) {
                leg->height = backrest_leg_h;
                leg->baseRadius = backrest_leg_radius;
            }else{
                leg->height = seat_leg_h;
                leg->baseRadius = seat_leg_radius;
            }

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
        std::vector<Object*> components {seat, backrest, seat_leg1, seat_leg2, seat_leg3, 
        seat_leg4, backrest_leg1, backrest_leg2};

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
        seat->transform(m);
        backrest->transform(m);
        seat_leg1->transform(m);
        seat_leg2->transform(m);
        seat_leg3->transform(m);
        seat_leg4->transform(m);
        backrest_leg1->transform(m);
        backrest_leg2->transform(m);
    }
    
};

#endif