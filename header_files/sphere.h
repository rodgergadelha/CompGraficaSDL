#include "object.h"
#include <vector>
#include <cmath>
#include <iostream>

#ifndef SPHERE_H
#define SPHERE_H


class Sphere : public Object {
public:
    Vec3 center;
    double radius;

    double intersection(Vec3 observer, Vec3 d) {
        Vec3 w = observer - center;
        std::vector<double> t;

        // Coeficientes da equação do segundo grau formada a partir
        // da substituição da equação do raio na equação da esfera
        double coefA = d ^ d;
        double coefB = 2 * (w ^ d);
        double coefC = (w ^ w) - (radius * radius);
        double delta = coefB*coefB - 4*coefA*coefC;

        if(delta < 0) return -1;

        double t1 = (-coefB + sqrt(delta))/(2*coefA);
        double t2 = (-coefB - sqrt(delta))/(2*coefA);
        double closestT = std::numeric_limits<double>::infinity();
        
        if(t1 > 0 && t1 < closestT) closestT = t1;
        if(t2 > 0 && t2 < closestT) closestT = t2;

        return closestT;
    }

    Vec3 getNormal(Vec3 intersectionPoint, Vec3 d) {
        return (intersectionPoint - center) / radius;
    }

};

#endif