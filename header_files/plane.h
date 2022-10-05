#include "vec3.h"
#include "object.h"
#include <vector>

#ifndef PLANE_H
#define PLANE_H

class Plane : public Object{
public:
    Vec3 pPi, normal;

    std::vector<double> intersection(Vec3 observer, Vec3 view) {
        std::vector<double> t;
        Vec3 w = observer - pPi;
        Vec3 direction = view - observer;
        if((direction ^ normal) == 0) return t;
        double ti = -(w ^ normal)/(direction ^ normal);

        if(ti > 0) t.push_back(ti);

        return t;
    }

    Vec3 getNormal(Vec3 intersectionPoint) {
        return normal;
    }

};

#endif