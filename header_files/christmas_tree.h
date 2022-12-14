#ifndef CHRISTMAS_TREE_H
#define CHRISTMAS_TREE_H

#include "vec3.h"
#include "matrix.h"
#include "complex_object.h"
#include "cube.h"
#include "cilinder.h"
#include <vector>
#include <iostream>

class ChristmasTree : public ComplexObject {
public:

    ChristmasTree(Vec3 center, double trunk_radius, double trunk_height,
    double leafs_radius, double leafs_height, double top_sphere_radius) {

        this->type = "christmas tree";
        this->kd.setCoordinates(0.4, 0.4, 0.4);
        this->ke.setCoordinates(0.1, 0.1, 0.1);
        this->ka.setCoordinates(0.5, 0.5, 0.5);
        this->shininess = 10;
        this->center = center;

        Cilinder *trunk = new Cilinder();
        trunk->center.setCoordinates(center.x, center.y, center.z);
        trunk->height = trunk_height;
        trunk->baseRadius = trunk_radius;
        trunk->u.setCoordinates(0, 1, 0);
        trunk->color.setCoordinates(74, 41, 24);
        trunk->kd = this->kd;
        trunk->ke = this->ke;
        trunk->ka = this->ka;
        trunk->shininess = this->shininess;
        trunk->basePlane.pPi = trunk->center*1;
        trunk->basePlane.normal = trunk->u*(-1);
        trunk->topPlane.pPi = trunk->center + (trunk->u)*(trunk->height);
        trunk->topPlane.normal = (trunk->u)*(trunk->height);
        
        Cone *leafs = new Cone(false);
        leafs->height = leafs_height;
        leafs->baseRadius = leafs_radius;
        leafs->center.setCoordinates(trunk->topPlane.pPi.x, trunk->topPlane.pPi.y - trunk->height/2, trunk->topPlane.pPi.z);
        leafs->n.setCoordinates(0, 1, 0);
        leafs->color.setCoordinates(0, 255, 0);
        leafs->kd = this->kd;
        leafs->ke = this->ke;
        leafs->ka = this->ka;
        leafs->shininess = this->shininess;

        Sphere *top_sphere = new Sphere();
        top_sphere->radius = top_sphere_radius;
        top_sphere->center.setCoordinates(leafs->center.x, leafs->center.y + leafs_height + top_sphere_radius, leafs->center.z);
        top_sphere->color.setCoordinates(255, 255, 0);
        top_sphere->kd.setCoordinates(0.9, 0.9, 0.9);
        top_sphere->ke.setCoordinates(0.9, 0.9, 0.9);
        top_sphere->ka.setCoordinates(0.9, 0.9, 0.9);
        top_sphere->shininess = 10;

        this->components = std::vector<Object*> {trunk, top_sphere, leafs};

        cluster = new Sphere();
        cluster->center.setCoordinates(this->center.x, this->center.y + trunk_height, this->center.z);
        cluster->radius = (trunk_height + leafs_height + top_sphere_radius);
    }
    
};

#endif