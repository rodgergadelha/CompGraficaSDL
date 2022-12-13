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
    bool hasBase;

    Cone() {
        this->type = "cone";
        this->hasBase = true;
    }

    Cone(bool hasBase) {
        this->type = "cone";
        this->hasBase = hasBase;
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

        if (((v - intersectionPoint1)^n) <= height
        && ((v - intersectionPoint1)^n) >= 0
        && (t1 > 0 && t1 < closestT)) {
            closestT = t1;
        }
        
        if (((v - intersectionPoint2)^n) <= height
        && ((v - intersectionPoint2)^n) >= 0
        & (t2 > 0 && t2 < closestT)) {
            closestT = t2;
        }

        if(hasBase) {
            double tBasePlane = basePlane.intersection(observer, d);
            if(tBasePlane > 0) {
                Vec3 piBasePlane = observer + d * tBasePlane;
                
                if((piBasePlane - center).getLength() <= baseRadius
                && (tBasePlane < closestT))
                    closestT = tBasePlane;
            }
        }

        return closestT;
    }

    Vec3 getNormal(Vec3 intersectionPoint, Vec3 d) {
        Vec3 w = getVertex() - intersectionPoint;
        Vec3 n0 = w.cross(this->n);
        Vec3 normal = n0.cross(w);

        return normal / normal.getLength();
    }

    void transform(Matrix m, bool rotateAxis = true) override {
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

        this->basePlane.pPi.setCoordinates(this->center.x, this->center.y, this->center.z);
        this->basePlane.normal.setCoordinates(-this->n.x, -this->n.y, -this->n.z);
    }

};

#endif