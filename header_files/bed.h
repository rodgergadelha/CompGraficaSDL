#ifndef BED_H
#define BED_H

#include "vec3.h"
#include "matrix.h"
#include "complex_object.h"
#include "cube.h"
#include "cilinder.h"
#include "world.h"
#include <vector>
#include <iostream>

class Bed : public ComplexObject {
public:
    
    Bed(Vec3 center, double width, double height, double depth, double legRadius, double legHeight) {
        this->type = "bed";
        this->kd.setCoordinates(0.9, 0.9, 0.9);
        this->ke.setCoordinates(0.6, 0.6, 0.6);
        this->ka.setCoordinates(0.8, 0.8, 0.8);
        this->shininess = 10;
        this->center = center;
        
        Cube *bed = new Cube(1, Vec3(0, 0, 0));
        bed->scale(width, height, depth);
        bed->translate(center.x, center.y, center.z);

        double pillow_width = depth/3;
        double pillow_height = width/2;
        Cube *pillow = new Cube(1, Vec3(0, 0, 0));
        pillow->setAllFacesColors(Vec3(255, 255, 255));
        pillow->scale(pillow_width, 1, pillow_height);
        pillow->translate(center.x, center.y + height/2 + 0.5, center.z - depth/2 + pillow_height/2);

        Cilinder *left_back_cilinder = new Cilinder();
        Cilinder *right_back_cilinder = new Cilinder();
        double back_cilinder_radius = legRadius;
        double back_cilinder_height = height * 0.8;
        left_back_cilinder->center.setCoordinates(center.x + width/2 - legRadius, center.y + height/2, center.z - depth/2 + legRadius);
        right_back_cilinder->center.setCoordinates(center.x - width/2 + legRadius, center.y + height/2, center.z - depth/2 + legRadius);

        Cube *head_board = new Cube(1, Vec3(0, 0, 0));
        head_board->setAllFacesColors(Vec3(0, 0, 0));
        head_board->scale(width - 2*back_cilinder_radius, back_cilinder_height, 2*back_cilinder_radius);
        head_board->translate(center.x, center.y + height/2 + back_cilinder_height/2, center.z - depth/2 + 0.5);

        Cilinder *leg1 = new Cilinder();
        Cilinder *leg2 = new Cilinder();
        Cilinder *leg3 = new Cilinder();
        Cilinder *leg4 = new Cilinder();
        leg1->center.setCoordinates(center.x + width/2 - legRadius, center.y - height/2 - legHeight, center.z - depth/2 + legRadius);
        leg2->center.setCoordinates(center.x - width/2 + legRadius, center.y - height/2 - legHeight, center.z - depth/2 + legRadius);
        leg3->center.setCoordinates(center.x + width/2 - legRadius, center.y - height/2 - legHeight, center.z + depth/2 - legRadius);
        leg4->center.setCoordinates(center.x - width/2 + legRadius, center.y - height/2 - legHeight, center.z + depth/2 - legRadius);
        
        std::vector<Cilinder*> legs {leg1, leg2, leg3, leg4, left_back_cilinder, right_back_cilinder};
        for(int i = 0; i < 6; i++) {
            Cilinder *leg = legs[i];

            if(i < 4) {
                leg->height = legHeight;
                leg->baseRadius = legRadius;
            }else{
                leg->height = back_cilinder_height;
                leg->baseRadius = back_cilinder_radius;
            }

            
            leg->u.setCoordinates(0, 1, 0);
            leg->color.setCoordinates(0, 0, 0);
            leg->kd = this->kd;
            leg->ke = this->ke;
            leg->ka = this->ka;
            leg->shininess = this->shininess;
            leg->basePlane.pPi = leg->center*1;
            leg->basePlane.normal = leg->u*(-1);
            leg->topPlane.pPi = leg->center + (leg->u)*(leg->height);
            leg->topPlane.normal = (leg->u)*(leg->height) / ((leg->u)*(leg->height)).getLength();
        }

        this->components = std::vector<Object*> {bed, head_board, leg1, leg2, leg3, leg4, pillow, left_back_cilinder, right_back_cilinder};
    }
    
};

#endif