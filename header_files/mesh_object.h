#ifndef MESH_OBJECT_H
#define MESH_OBJECT_H

#include "vec3.h"
#include "matrix.h"
#include "object.h"
#include "plane.h"
#include "face.h"
#include <map>
#include <iostream>

class MeshObject : public Object {
public:
    Vec3 center, normal;
    std::vector<Vec3> vertices;
    std::vector<Face> faces;

    double intersection(Vec3 observer, Vec3 direction) {
        double closestT = std::numeric_limits<double>::infinity();

        for(auto face : faces) {
            Vec3 n = face.getNormal();

            double t = face.intersection(observer, direction);

            if(t > 0 && t < closestT) {
                closestT = t;
                Vec3 n = face.getNormal();
                this->normal.setCoordinates(n.x, n.y, n.z);
            }
        }

        return closestT;
    }

    Vec3 getNormal(Vec3 intersectionPoint, Vec3 d) { return this->normal; }

};

#endif