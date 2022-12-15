#ifndef SNOW_MAN_H
#define SNOW_MAN_H

#include "vec3.h"
#include "matrix.h"
#include "cilinder.h"
#include "sphere.h"
#include "cone.h"
#include "complex_object.h"
#include <vector>
#include <iostream>

class Snowman : public ComplexObject {
public:
   
    Snowman(Vec3 center, double head_radius, double body_radius, double nose_radius, double nose_height,
        double hat_radius, double hat_height) {
    
        this->type = "snow man";
        this->kd.setCoordinates(0.9, 0.9, 0.9);
        this->ke.setCoordinates(0.6, 0.6, 0.6);
        this->ka.setCoordinates(0.8, 0.8, 0.8);
        this->shininess = 10;
        this->center = center;

        Sphere *body = new Sphere();
        body->radius = body_radius;
        body->center.setCoordinates(center.x, center.y, center.z);
        body->color.setCoordinates(255, 255, 255);
        body->kd = this->kd;
        body->ke = this->ke;
        body->ka = this->ka;
        body->shininess = this->shininess;

        Sphere *middle_tie = new Sphere();
        middle_tie->radius = nose_radius;
        middle_tie->center.setCoordinates(body->center.x, body->center.y + body_radius, body->center.z + 3*nose_radius);
        middle_tie->color.setCoordinates(255, 0, 0);
        middle_tie->kd = this->kd;
        middle_tie->ke = this->ke;
        middle_tie->ka = this->ka;
        middle_tie->shininess = this->shininess;

        Cone *tie_left = new Cone();
        tie_left->height = nose_height * 2;
        tie_left->baseRadius = middle_tie->radius;
        tie_left->center.setCoordinates(middle_tie->center.x - middle_tie->radius - nose_height, middle_tie->center.y, middle_tie->center.z);
        tie_left->n.setCoordinates(1, 0, 0);
        tie_left->color = middle_tie->color * 1;
        tie_left->kd = this->kd;
        tie_left->ke = this->ke;
        tie_left->ka = this->ka;
        tie_left->shininess = this->shininess;

        Cone *tie_right = new Cone();
        tie_right->height = tie_left->height;
        tie_right->baseRadius = tie_left->baseRadius;
        tie_right->center.setCoordinates(middle_tie->center.x + middle_tie->radius + nose_height, middle_tie->center.y, middle_tie->center.z);
        tie_right->n.setCoordinates(-1, 0, 0);
        tie_right->color = middle_tie->color * 1;
        tie_right->kd = this->kd;
        tie_right->ke = this->ke;
        tie_right->ka = this->ka;
        tie_right->shininess = this->shininess;

        Sphere *head = new Sphere();
        head->radius = head_radius;
        head->center.setCoordinates(center.x, center.y + body_radius + head_radius, center.z);
        head->color.setCoordinates(255, 255, 255);
        head->kd = this->kd;
        head->ke = this->ke;
        head->ka = this->ka;
        head->shininess = this->shininess;

        Cilinder *hat_base = new Cilinder();
        hat_base->center.setCoordinates(head->center.x, head->center.y + head_radius, head->center.z);
        hat_base->height = 0.7;
        hat_base->baseRadius = hat_radius * 2;
        hat_base->u.setCoordinates(0, 1, 0);
        hat_base->color.setCoordinates(0, 0, 0);
        hat_base->kd = this->kd;
        hat_base->ke = this->ke;
        hat_base->ka = this->ka;
        hat_base->shininess = this->shininess;
        hat_base->basePlane.pPi = hat_base->center*1;
        hat_base->basePlane.normal = hat_base->u*(-1);
        hat_base->topPlane.pPi = hat_base->center + (hat_base->u)*(hat_base->height);
        hat_base->topPlane.normal = (hat_base->u)*(hat_base->height);

        Cilinder *hat = new Cilinder();
        hat->center.setCoordinates(hat_base->center.x, hat_base->center.y + hat_base->height, hat_base->center.z);
        hat->height = hat_height;
        hat->baseRadius = hat_radius;
        hat->u.setCoordinates(0, 1, 0);
        hat->color.setCoordinates(0, 0, 0);
        hat->kd = this->kd;
        hat->ke = this->ke;
        hat->ka = this->ka;
        hat->shininess = this->shininess;
        hat->basePlane.pPi = hat->center*1;
        hat->basePlane.normal = hat->u*(-1);
        hat->topPlane.pPi = hat->center + (hat->u)*(hat->height);
        hat->topPlane.normal = (hat->u)*(hat->height);

        Sphere *eye1 = new Sphere();
        eye1->radius = head->radius/8;
        eye1->center.setCoordinates(head->center.x - head_radius/2, head->center.y + head_radius/4, head->center.z + head_radius - head_radius/8);
        eye1->color.setCoordinates(0, 0, 0);
        eye1->kd = this->kd;
        eye1->ke = this->ke;
        eye1->ka = this->ka;
        eye1->shininess = this->shininess;

        Sphere *eye2 = new Sphere();
        eye2->radius = eye1->radius;
        eye2->center.setCoordinates(head->center.x + head_radius/2, head->center.y + head_radius/4, head->center.z + head_radius - head_radius/8);
        eye2->color.setCoordinates(0, 0, 0);
        eye2->kd = this->kd;
        eye2->ke = this->ke;
        eye2->ka = this->ka;
        eye2->shininess = this->shininess;

        Cone *nose = new Cone(false);
        nose->height = nose_height;
        nose->baseRadius = nose_radius;
        nose->center.setCoordinates(head->center.x, head->center.y, head->center.z + head_radius);
        nose->n.setCoordinates(0, 0, 1);
        nose->color.setCoordinates(255, 0, 0);
        nose->kd = this->kd;
        nose->ke = this->ke;
        nose->ka = this->ka;
        nose->shininess = this->shininess;
       
        this->components = std::vector<Object*> {body, hat, hat_base, head, eye1, eye2, nose, middle_tie, tie_left, tie_right};
    
        cluster = new Sphere();
        cluster->center.setCoordinates(center.x, center.y, center.z);
        cluster->radius = body_radius*2 + head_radius + hat_height;
    }
    
};

#endif