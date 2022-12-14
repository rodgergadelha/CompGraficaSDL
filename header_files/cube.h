#ifndef CUBE_H
#define CUBE_H

#include "vec3.h"
#include "matrix.h"
#include "mesh_object.h"
#include <vector>
#include <iostream>

class Cube : public MeshObject {
public:
    Cube() {
        this->type = "cube";
        this->size = 0;
        this->center = Vec3(0, 0, 0);
        this->kd.setCoordinates(0.9, 0.9, 0.9);
        this->ke.setCoordinates(0.6, 0.6, 0.6);
        this->ka.setCoordinates(0.8, 0.8, 0.8);
        this->shininess = 10;
    }

    Cube(double size, Vec3 center) {
        this->type = "cube";
        this->size = size;
        this->center = center;
        this->kd.setCoordinates(0.9, 0.9, 0.9);
        this->ke.setCoordinates(0.6, 0.6, 0.6);
        this->ka.setCoordinates(0.8, 0.8, 0.8);
        this->shininess = 10;

        this->vertices = {  
            new Vec3(center.x - size/2, center.y - size/2, center.z + size/2),
            new Vec3(center.x + size/2, center.y - size/2, center.z + size/2),
            new Vec3(center.x + size/2, center.y + size/2, center.z + size/2),
            new Vec3(center.x - size/2, center.y + size/2, center.z + size/2),
            new Vec3(center.x - size/2, center.y + size/2, center.z - size/2),
            new Vec3(center.x - size/2, center.y - size/2, center.z - size/2),
            new Vec3(center.x + size/2, center.y - size/2, center.z - size/2),
            new Vec3(center.x + size/2, center.y + size/2, center.z - size/2)
        };
        this->faces = {
            new Face(vertices[0], vertices[1], vertices[3]), new Face(vertices[1], vertices[2], vertices[3]),
            new Face(vertices[1], vertices[6], vertices[2]), new Face(vertices[2], vertices[6], vertices[7]),
            new Face(vertices[5], vertices[7], vertices[6]), new Face(vertices[5], vertices[4], vertices[7]),
            new Face(vertices[0], vertices[4], vertices[5]), new Face(vertices[3], vertices[4], vertices[0]),
            new Face(vertices[4], vertices[2], vertices[7]), new Face(vertices[4], vertices[3], vertices[2]),
            new Face(vertices[0], vertices[5], vertices[1]), new Face(vertices[1], vertices[5], vertices[6])
        };

        this->cluster.center = this->center;
        this->cluster.radius = size;
    }
};

#endif