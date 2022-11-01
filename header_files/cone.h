#include "vec3.h"
#include "object.h"
#include "plane.h"
#include <iostream>

#ifndef CONE_H
#define CONE_H

class Cone : public Object {
public:
    Vec3 baseCenter, n, vertex;
    Plane basePlane;
    double height, baseRadius, theta;

    Vec3 getVertex() {
        return (baseCenter + n*height);
    }

    std::vector<double> intersection(Vec3 observer, Vec3 d) {
        Vec3 vertex = getVertex();
        Vec3 v = vertex - observer;
        std::vector<double> t;

        double coefA = (d ^ n)*(d ^ n) - (d ^ d)*cos(theta)*cos(theta);
        double coefB = 2 * ((v ^ d)*cos(theta)*cos(theta) - (v ^ n)*(d ^ n));
        double coefC = (v ^ n)*(v ^ n) - (v ^ v)*cos(theta)*cos(theta);
        double delta = (coefB * coefB) - (4 * coefA * coefC);

        if(delta < 0) return t;

        double t1 = (-coefB + sqrt(delta))/(2*coefA);
        double t2 = (-coefB - sqrt(delta))/(2*coefA);

        Vec3 intersectionPoint1 = observer + d*t1;
        Vec3 intersectionPoint2 = observer + d*t2;

        t.push_back(std::numeric_limits<double>::infinity());
        t.push_back(std::numeric_limits<double>::infinity());
        
        if (((v - intersectionPoint1)^n) < height
        && ((v - intersectionPoint1)^n) > 0) {
            t.at(0) = t1;
        }
        
        if (((v - intersectionPoint2)^n) < height
        && ((v - intersectionPoint2)^n) > 0) {
            t.at(1) = t2;
        }

        return t;
    }

    std::vector<Vec3> getTMatrixNormal(Vec3 d) {
        Vec3 col1 = Vec3(1 - d.x * d.x,
                        -d.y * d.x,
                        -d.z * d.x);
        Vec3 col2 = Vec3(-d.x * d.y,
                        1 - d.y * d.y,
                        -d.z * d.y);
        Vec3 col3 = Vec3(-d.x * d.z,
                        -d.y * d.z,
                        1 - d.z * d.z);
        
        std::vector<Vec3> tMatrix;
        tMatrix.push_back(col1);
        tMatrix.push_back(col2);
        tMatrix.push_back(col3);

        return tMatrix;
    }

    Vec3 getNormal(Vec3 intersectionPoint, Vec3 d) {
        std::vector <Vec3> tMatrix = getTMatrixNormal(d);
        Vec3 ipMinusBc = intersectionPoint - baseCenter;
        Vec3 bigNormal = Vec3((tMatrix.at(0).x * ipMinusBc.x) + (tMatrix.at(1).x * ipMinusBc.y) + (tMatrix.at(2).x * ipMinusBc.z),
        (tMatrix.at(0).y * ipMinusBc.x) + (tMatrix.at(1).y * ipMinusBc.y) + (tMatrix.at(2).y * ipMinusBc.z),
        (tMatrix.at(0).z * ipMinusBc.x) + (tMatrix.at(1).z * ipMinusBc.y) + (tMatrix.at(2).z * ipMinusBc.z));

        return bigNormal / bigNormal.getLength();
    }

};

#endif