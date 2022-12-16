#ifndef MASTER_SHIELD_H
#define MASTER_SHIELD_H

#include "vec3.h"
#include "matrix.h"
#include "cube.h"
#include "complex_object.h"
#include <vector>
#include <iostream>

class MasterShield : public ComplexObject {
public:
   
    MasterShield(Vec3 center, double shield_w, double shield_h) {
        this->type = "master shield";
        this->kd.setCoordinates(0.9, 0.9, 0.9);
        this->ke.setCoordinates(0.5, 0.5, 0.5);
        this->ka.setCoordinates(0.7, 0.7, 0.7);
        this->shininess = 10;
        this->center = center;

        double shield_connector_w = shield_w/8;
        double shield_connector_h = shield_h/8;

        Cube *mid_shield = new Cube(1, Vec3(0, 0, 0));
        mid_shield->scale(shield_w, shield_h, 1);
        mid_shield->translate(center.x, center.y, center.z);
        mid_shield->loadImageAllFaces("textures/screen.jpg");

        Cube *shield_connector1 = new Cube(1, Vec3(0, 0, 0));
        shield_connector1->scale(shield_connector_w, shield_connector_h, 1);
        shield_connector1->translate(mid_shield->center.x - shield_w/2 - shield_connector_w/2, mid_shield->center.y, mid_shield->center.z);
        shield_connector1->setAllFacesColors(Vec3(0, 0, 0));

        Cube *shield_connector2 = new Cube(1, Vec3(0, 0, 0));
        shield_connector2->scale(shield_connector_w, shield_connector_h, 1);
        shield_connector2->translate(mid_shield->center.x + shield_w/2 + shield_connector_w/2, mid_shield->center.y, mid_shield->center.z);
        shield_connector2->setAllFacesColors(Vec3(0, 0, 0));

        Cube *left_shield = new Cube(1, Vec3(0, 0, 0));
        left_shield->scale(shield_w, shield_h, 1);
        left_shield->rotateY(-25);
        left_shield->translate(shield_connector1->center.x - shield_connector_w/2 - shield_w/2, shield_connector1->center.y, shield_connector1->center.z - 1);
        left_shield->loadImageAllFaces("textures/screen.jpg");

        Cube *right_shield = new Cube(1, Vec3(0, 0, 0));
        right_shield->scale(shield_w, shield_h, 1);
        right_shield->rotateY(25);
        right_shield->translate(shield_connector2->center.x + shield_connector_w/2 + shield_w/2, shield_connector2->center.y, shield_connector2->center.z - 1);
        right_shield->loadImageAllFaces("textures/screen.jpg");

        this->components = std::vector<Object*> {mid_shield, left_shield, right_shield, shield_connector1, shield_connector2};
    
        cluster = new Sphere();
        cluster->center.setCoordinates(mid_shield->center.x, mid_shield->center.y, mid_shield->center.z);
        cluster->radius = std::max(shield_w, shield_h) * 3;
    }
    
};

#endif