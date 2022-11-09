#ifndef FACE_H
#define FACE_H

#include "vec3.h"
#include "matrix.h"
#include "object.h"
#include "plane.h"
#include <map>
#include <iostream>

class Face {
public:
    Vec3 p1, p2, p3;

    Face(Vec3 p1, Vec3 p2, Vec3 p3) {
        this->p1 = p1;
        this->p2 = p2;
        this->p3 = p3;
    }

    bool contains(Vec3 point) {
        Vec3 normal = getNormal();
        Vec3 r1 = p2 - p1;
        Vec3 r2 = p3 - p1;
        double area = (r1.cross(r2)) ^ normal;
        double c1 = (((p1 - point).cross(p2 - point)) ^ normal) / area;
        double c2 = (((p3 - point).cross(p1 - point)) ^ normal) / area;
        double c3 = (((p2 - point).cross(p3 - point)) ^ normal) / area;

        return (c1 >= 0 - 0.001) && (c2 >= 0 - 0.001) && (c3 >= 0 - 0.001);
    }

    double intersection(Vec3 observer, Vec3 direction) {
        Vec3 n = getNormal();

        if((direction ^ n) == 0) return -1;

        double t = -((observer - p1) ^ n) / (direction ^ n);
        Vec3 intersectionPoint = observer + direction*t;

        if(contains(intersectionPoint)) return t;
        return -1;
    }

    Vec3 getNormal() {
        Vec3 r1 = p2 - p1;
        Vec3 r2 = p3 - p1;
        Vec3 n = r1.cross(r2);
        return n / (n.getLength());
    }
};

#endif