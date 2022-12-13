#ifndef CLOSET_H
#define CLOSET_H

#include "vec3.h"
#include "matrix.h"
#include "complex_object.h"
#include "cube.h"
#include "cilinder.h"
#include "world.h"
#include <vector>
#include <iostream>

class Closet : public ComplexObject {
public:
    
    Closet(Vec3 center, Vec3 color, double width, double height, double depth, double legRadius, double legHeight) {
        this->type = "closet";
        this->kd.setCoordinates(0.9, 0.9, 0.9);
        this->ke.setCoordinates(0.6, 0.6, 0.6);
        this->ka.setCoordinates(0.8, 0.8, 0.8);
        this->shininess = 10;
        
        Cube *closet = new Cube(1, Vec3(0, 0, 0));
        closet->color = color;
        closet->scale(width, height, depth);
        closet->translate(center.x, center.y, center.z);

        Cilinder *leg1 = new Cilinder();
        Cilinder *leg2 = new Cilinder();
        Cilinder *leg3 = new Cilinder();
        Cilinder *leg4 = new Cilinder();
        
        leg1->center.setCoordinates(center.x + width/2 - 2, center.y - height/2 - legHeight, center.z - depth/2 + 2);
        leg2->center.setCoordinates(center.x - width/2 + 2, center.y - height/2 - legHeight, center.z - depth/2 + 2);
        leg3->center.setCoordinates(center.x + width/2 - 2, center.y - height/2 - legHeight, center.z + depth/2 - 2);
        leg4->center.setCoordinates(center.x - width/2 + 2, center.y - height/2 - legHeight, center.z + depth/2 - 2);
        
        std::vector<Cilinder*> legs {leg1, leg2, leg3, leg4};

        for(auto leg : legs) {
            leg->height = legHeight;
            leg->baseRadius = legRadius;
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

        this->components = std::vector<Object*> {closet, leg1, leg2, leg3, leg4};
    }
    
};

#endif