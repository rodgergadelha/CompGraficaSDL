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

    std::vector<double> intersection(Vec3 observer, Vec3 view) {
        Vec3 w = observer - center;
        Vec3 direction = view - observer;
        std::vector<double> t;

        // Coeficientes da equação do segundo grau formada a partir
        // da substituição da equação do raio na equação da esfera
        double coefA = direction ^ direction;
        double coefB = 2 * (w ^ direction);
        double coefC = (w ^ w) - (radius * radius);
        double delta = coefB*coefB - 4*coefA*coefC;

        if(delta < 0) return t;

        double t1 = (-coefB + sqrt(delta))/(2*coefA);
        double t2 = (-coefB - sqrt(delta))/(2*coefA);
        t.push_back(t1);
        t.push_back(t2);

        return t;
    }

    Vec3 getNormal(Vec3 intersectionPoint) {
        return (intersectionPoint - center) / radius;
    }

};

#endif