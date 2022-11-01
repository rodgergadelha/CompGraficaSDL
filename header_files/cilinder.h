#include "vec3.h"
#include "object.h"
#include "plane.h"
#include <iostream>

#ifndef CILINDER_H
#define CILINDER_H

class Cilinder : public Object {
public:
    Vec3 baseCenter, u;
    Plane basePlane, topPlane;
    double height, baseRadius;

    double intersection(Vec3 observer, Vec3 d) {
        Vec3 v = (observer - baseCenter) - u*((observer - baseCenter) ^ u);
        Vec3 w = d - u*(d ^ u);

        double coefA = w ^ w;
        double coefB = 2 * (v ^ w);
        double coefC = (v ^ v) - (baseRadius * baseRadius);
        double delta = (coefB * coefB) - (4 * coefA * coefC);

        if(delta < 0) return -1;

        double t1 = (-coefB + sqrt(delta))/(2*coefA);
        double t2 = (-coefB - sqrt(delta))/(2*coefA);

        Vec3 intersectionPoint1 = observer + d*t1;
        Vec3 intersectionPoint2 = observer + d*t2;

        double closestT = std::numeric_limits<double>::infinity();
        
        if (((intersectionPoint1 - baseCenter)^u) <= height
        && ((intersectionPoint1 - baseCenter)^u) >= 0
        && (t1 > 0 && t1 < closestT)) {
            closestT = t1;
        }
        
        if (((intersectionPoint2 - baseCenter)^u) <= height
        && ((intersectionPoint2 - baseCenter)^u) >= 0
        && (t2 > 0 && t2 < closestT)) {
            closestT = t2;
        }

        double tBasePlane = basePlane.intersection(observer, d);
        if(tBasePlane > 0) {
            Vec3 piBasePlane = observer + d * tBasePlane;
            
            if((piBasePlane - baseCenter).getLength() <= baseRadius
            && (tBasePlane < closestT))
                closestT = tBasePlane;
        }

        double tTopPlane = topPlane.intersection(observer, d);
        if(tTopPlane > 0) {
            Vec3 piTopPlane = observer + d * tTopPlane;
            
            if((piTopPlane - baseCenter).getLength() <= baseRadius
            && (tTopPlane < closestT))
                closestT = tTopPlane;
        }

        return closestT;
    }

    std::vector<Vec3> getTMatrixNormal(Vec3 direction) {
        Vec3 col1 = Vec3(1 - u.x * u.x,
                        -u.y * u.x,
                        -u.z * u.x);
        Vec3 col2 = Vec3(-u.x * u.y,
                        1 - u.y * u.y,
                        -u.z * u.y);
        Vec3 col3 = Vec3(-u.x * u.z,
                        -u.y * u.z,
                        1 - u.z * u.z);
        
        std::vector<Vec3> tMatrix;
        tMatrix.push_back(col1);
        tMatrix.push_back(col2);
        tMatrix.push_back(col3);

        return tMatrix;
    }

    Vec3 getNormal(Vec3 intersectionPoint, Vec3 d) {
        std::vector <Vec3> tMatrix = getTMatrixNormal(u);
        Vec3 ipMinusBc = intersectionPoint - baseCenter;
        Vec3 bigNormal = Vec3((tMatrix.at(0).x * ipMinusBc.x) + (tMatrix.at(1).x * ipMinusBc.y) + (tMatrix.at(2).x * ipMinusBc.z),
        (tMatrix.at(0).y * ipMinusBc.x) + (tMatrix.at(1).y * ipMinusBc.y) + (tMatrix.at(2).y * ipMinusBc.z),
        (tMatrix.at(0).z * ipMinusBc.x) + (tMatrix.at(1).z * ipMinusBc.y) + (tMatrix.at(2).z * ipMinusBc.z));

        return bigNormal / bigNormal.getLength();
    }

};

#endif