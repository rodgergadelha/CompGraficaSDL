#ifndef ICOSAHEDRON_H
#define ICOSAHEDRON_H

#include "vec3.h"
#include "matrix.h"
#include "mesh_object.h"
#include <vector>
#include <iostream>

class Icosahedron : public MeshObject {
public:

    Icosahedron(double size, Vec3 center) {
        this->type = "icosahedron";
        this->center = Vec3(0, 0, 0);
        double c = (1 + sqrt(5)) / 4;
        this->size = size * c;

        this->vertices = {
            new Vec3(0.5, 0.0, c),
            new Vec3( 0.5,  0.0, -c),
            new Vec3(-0.5,  0.0, c),
            new Vec3(-0.5,  0.0, -c),
            new Vec3(c, 0.5, 0.0),
            new Vec3(c, -0.5, 0.0),
            new Vec3(-c, 0.5, 0.0),
            new Vec3(-c, -0.5, 0.0),
            new Vec3(0.0, c, 0.5),
            new Vec3(0.0, c, -0.5),
            new Vec3(0.0, -c, 0.5),
            new Vec3(0.0, -c, -0.5)
        };
        this->faces = {
            new Face(vertices[0], vertices[2], vertices[10]),
            new Face(vertices[0], vertices[10],  vertices[5]),
            new Face(  vertices[0],  vertices[5],  vertices[4] ),
            new Face(  vertices[0],  vertices[4],  vertices[8] ),
            new Face(  vertices[0],  vertices[8],  vertices[2] ),
            new Face(  vertices[3],  vertices[1], vertices[11] ),
            new Face(  vertices[3], vertices[11],  vertices[7] ),
            new Face(  vertices[3],  vertices[7],  vertices[6] ),
            new Face(  vertices[3],  vertices[6],  vertices[9] ),
            new Face(  vertices[3],  vertices[9],  vertices[1] ),
            new Face(  vertices[2],  vertices[6],  vertices[7] ),
            new Face(  vertices[2],  vertices[7], vertices[10] ),
            new Face( vertices[10],  vertices[7], vertices[11] ),
            new Face( vertices[10], vertices[11],  vertices[5] ),
            new Face(  vertices[5], vertices[11],  vertices[1] ),
            new Face(  vertices[5],  vertices[1],  vertices[4] ),
            new Face(  vertices[4],  vertices[1],  vertices[9] ),
            new Face(  vertices[4],  vertices[9],  vertices[8] ),
            new Face(  vertices[8],  vertices[9],  vertices[6] ),
            new Face(  vertices[8],  vertices[6],  vertices[2] )
        };
        
        this->setAllFacesColors(Vec3(9, 152, 195));

        this->scale(size, size, size);
        this->translate(center.x, center.y, center.z);
        this->cluster.center.setCoordinates(center.x, center.y, center.z);
        this->cluster.radius = size * c * 2;
    }
};

#endif