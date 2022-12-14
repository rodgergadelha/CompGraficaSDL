#ifndef TABLE_H
#define TABLE_H

#include "vec3.h"
#include "matrix.h"
#include "cube.h"
#include "complex_object.h"
#include <vector>
#include <iostream>

class Table : public ComplexObject {
public:
   
    Table(Vec3 center, double cover_w, double cover_h, double cover_d, double leg_w, double leg_h, double leg_d) {
        this->type = "table";
        this->kd.setCoordinates(0.9, 0.9, 0.9);
        this->ke.setCoordinates(0.6, 0.6, 0.6);
        this->ka.setCoordinates(0.8, 0.8, 0.8);
        this->shininess = 10;
        this->center = center;
        
        Cube *cover = new Cube(1, Vec3(0, 0, 0));
        cover->scale(cover_w, cover_d, cover_h);
        cover->translate(center.x, center.y, center.z);

        Cube *leg1 = new Cube(1, Vec3(0, 0, 0));
        leg1->scale(leg_w, leg_h, leg_d);
        leg1->translate(center.x + cover_w/2 - leg_w/2, center.y - leg_h/2, center.z - cover_h/2 + leg_d/2);

        Cube *leg2 = new Cube(1, Vec3(0, 0, 0));
        leg2->scale(leg_w, leg_h, leg_d);
        leg2->translate(center.x - cover_w/2 + leg_w/2, center.y - leg_h/2, center.z - cover_h/2 + leg_d/2);

        Cube *leg3 = new Cube(1, Vec3(0, 0, 0));
        leg3->scale(leg_w, leg_h, leg_d);
        leg3->translate(center.x + cover_w/2 - leg_w/2, center.y - leg_h/2, center.z + cover_h/2 - leg_d/2);

        Cube *leg4 = new Cube(1, Vec3(0, 0, 0));
        leg4->scale(leg_w, leg_h, leg_d);
        leg4->translate(center.x - cover_w/2 + leg_w/2, center.y - leg_h/2, center.z + cover_h/2 - leg_d/2);

        this->components = std::vector<Object*> {cover, leg1, leg2, leg3, leg4};

        cluster = new Sphere();
        cluster->center.setCoordinates(cover->center.x, cover->center.y, cover->center.z);
        cluster->radius = std::max(cover_h, std::max(cover_w, cover_d)) + leg_h;
    }
    
};

#endif