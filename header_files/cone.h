#ifndef CONE_H
#define CONE_H

#include "vec3.h"
#include "matrix.h"
#include "object.h"
#include "plane.h"
#include <iostream>

class Cone : public Object {
public:
    Vec3 n, vertex;
    Plane basePlane;
    double height, baseRadius;

    Cone() {
        this->type = "cone";
    }

    Vec3 getVertex() {
        return (center + n*height);
    }

    double intersection(Vec3 observer, Vec3 d) {
        Vec3 vertex = getVertex();
        Vec3 v = vertex - observer;
        double cosTheta2 = (height*height)/((height*height) + (baseRadius*baseRadius));

        double coefA = (d ^ n)*(d ^ n) - (d ^ d)*cosTheta2;
        double coefB = 2 * ((v ^ d)*cosTheta2 - (v ^ n)*(d ^ n));
        double coefC = (v ^ n)*(v ^ n) - (v ^ v)*cosTheta2;
        double delta = (coefB * coefB) - (4 * coefA * coefC);

        if(delta < 0) return -1;

        double t1 = (-coefB + sqrt(delta))/(2*coefA);
        double t2 = (-coefB - sqrt(delta))/(2*coefA);

        Vec3 intersectionPoint1 = observer + d*t1;
        Vec3 intersectionPoint2 = observer + d*t2;

        double closestT = std::numeric_limits<double>::infinity();

        if (((v - intersectionPoint1)^n) < height
        && ((v - intersectionPoint1)^n) > 0
        && (t1 > 0 && t1 < closestT)) {
            closestT = t1;
        }
        
        if (((v - intersectionPoint2)^n) < height
        && ((v - intersectionPoint2)^n) > 0
        & (t2 > 0 && t2 < closestT)) {
            closestT = t2;
        }

        double tBasePlane = basePlane.intersection(observer, d);
        if(tBasePlane > 0) {
            Vec3 piBasePlane = observer + d * tBasePlane;
            
            if((piBasePlane - center).getLength() <= baseRadius
            && (tBasePlane < closestT))
                closestT = tBasePlane;
        }

        return closestT;
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
        if(((intersectionPoint - basePlane.pPi) ^ n) < 0.0001) return basePlane.normal;

        std::vector <Vec3> tMatrix = getTMatrixNormal(n);
        Vec3 ipMinusBc = intersectionPoint - center;
        Vec3 bigNormal = Vec3((tMatrix.at(0).x * ipMinusBc.x) + (tMatrix.at(1).x * ipMinusBc.y) + (tMatrix.at(2).x * ipMinusBc.z),
        (tMatrix.at(0).y * ipMinusBc.x) + (tMatrix.at(1).y * ipMinusBc.y) + (tMatrix.at(2).y * ipMinusBc.z),
        (tMatrix.at(0).z * ipMinusBc.x) + (tMatrix.at(1).z * ipMinusBc.y) + (tMatrix.at(2).z * ipMinusBc.z));

        return bigNormal / bigNormal.getLength();
    }

    void transform(Matrix m) {
        Matrix centerMatrix = Vec3::vec3ToMatrix(this->center);
        Matrix transformedCenter = m * centerMatrix;
        this->center.setCoordinates(transformedCenter.getElementAt(0,0),
                                    transformedCenter.getElementAt(1,0),
                                    transformedCenter.getElementAt(2,0));

        Matrix normalMatrix = Vec3::vec3ToMatrix(this->n);
        normalMatrix.setElementAt(3, 0, 0);
        Matrix transformedNormal = m * normalMatrix;
        this->n.setCoordinates(transformedNormal.getElementAt(0,0),
                                    transformedNormal.getElementAt(1,0),
                                    transformedNormal.getElementAt(2,0));
        Vec3 normalUnit = this->n/this->n.getLength();
        this->n.setCoordinates(normalUnit.x, normalUnit.y, normalUnit.z);
    }

};

#endif