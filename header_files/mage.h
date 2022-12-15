#ifndef MAGE_H
#define MAGE_H

#include "vec3.h"
#include "matrix.h"
#include "cilinder.h"
#include "cube.h"
#include "cone.h"
#include "complex_object.h"
#include <vector>
#include <iostream>

class Mage : public ComplexObject {
public:
   
    Mage(Vec3 center, double hat_height, double head_radius, 
        double body_width, double body_height, double body_depth) {
    
        this->type = "mage";
        this->kd.setCoordinates(0.9, 0.9, 0.9);
        this->ke.setCoordinates(0.6, 0.6, 0.6);
        this->ka.setCoordinates(0.8, 0.8, 0.8);
        this->shininess = 10;
        this->center = center;

        Cube *body = new Cube(1, Vec3(0, 0, 0));
        body->scale(body_width, body_height, body_depth);
        body->translate(center.x, center.y, center.z);

        double leg_height = body_height;
        double leg_radius = body_width/4;

        Cilinder *leg1 = new Cilinder();
        Cilinder *leg2 = new Cilinder();
        Cilinder *arm1 = new Cilinder();
        Cilinder *arm2 = new Cilinder();
        arm1->u.setCoordinates(0, 0, -1);
        arm2->u.setCoordinates(0, 1, 0);
        leg1->u.setCoordinates(0, 1, 0);
        leg2->u.setCoordinates(0, 1, 0);
        leg1->center.setCoordinates(center.x - leg_radius, center.y - body_height/2 - leg_height, center.z);
        leg2->center.setCoordinates(center.x + leg_radius, center.y - body_height/2 - leg_height, center.z);
        arm1->center.setCoordinates(center.x - body_width/2 - leg_radius, center.y + body_height/2 - leg_radius, center.z + leg_height);
        arm2->center.setCoordinates(center.x + body_width/2 + leg_radius, center.y - body_height/2, center.z);

        Cilinder *staff = new Cilinder();
        staff->u.setCoordinates(0, 1, 0);
        staff->height = body_height + leg_height;
        staff->center.setCoordinates(arm1->center.x, arm1->center.y - staff->height/1.5, arm1->center.z);
        staff->baseRadius = leg_radius * 0.28;
        staff->color.setCoordinates(255, 0, 0);
        staff->kd = this->kd;
        staff->ke = this->ke;
        staff->ka = this->ka;
        staff->shininess = this->shininess;
        staff->basePlane.pPi = staff->center*1;
        staff->basePlane.normal = staff->u*(-1);
        staff->topPlane.pPi = staff->center + (staff->u)*(staff->height);
        staff->topPlane.normal = (staff->u)*(staff->height);

        Sphere *staff_top = new Sphere();
        staff_top->radius = staff->baseRadius * 2;
        staff_top->center.setCoordinates(staff->topPlane.pPi.x, staff->topPlane.pPi.y + staff_top->radius, staff->topPlane.pPi.z);
        staff_top->color.setCoordinates(255, 255, 255);
        staff_top->kd = this->kd;
        staff_top->ke = this->ke;
        staff_top->ka = this->ka;
        staff_top->shininess = this->shininess;

        std::vector<Cilinder*> legs = {leg1, leg2, arm1, arm2};

        for(auto leg : legs) {
            leg->height = leg_height;
            leg->baseRadius = leg_radius;
            leg->color.setCoordinates(255, 0, 0);
            leg->kd = this->kd;
            leg->ke = this->ke;
            leg->ka = this->ka;
            leg->shininess = this->shininess;
            leg->basePlane.pPi = leg->center*1;
            leg->basePlane.normal = leg->u*(-1);
            leg->topPlane.pPi = leg->center + (leg->u)*(leg->height);
            leg->topPlane.normal = (leg->u)*(leg->height);
        }
       
        Sphere *head = new Sphere();
        head->radius = head_radius;
        head->center.setCoordinates(center.x, center.y + body_height/2 + head_radius, center.z);
        head->color.setCoordinates(255, 255, 255);
        head->kd = this->kd;
        head->ke = this->ke;
        head->ka = this->ka;
        head->shininess = this->shininess;

        Cone *hat = new Cone(false);
        hat->height = hat_height;
        hat->baseRadius = head_radius;
        hat->center.setCoordinates(head->center.x, head->center.y + head_radius*2/3, head->center.z);
        hat->n.setCoordinates(0, 1, 0);
        hat->color.setCoordinates(255, 0, 0);
        hat->kd = this->kd;
        hat->ke = this->ke;
        hat->ka = this->ka;
        hat->shininess = this->shininess;
       
        this->components = std::vector<Object*> {hat, head, body, arm1, arm2, leg1, leg2, staff, staff_top};
    
        cluster = new Sphere();
        cluster->center.setCoordinates(center.x, center.y, center.z);
        cluster->radius = (std::max(body_height, std::max(body_width, body_depth)) + head_radius + hat_height + leg_height);
    }
    
};

#endif