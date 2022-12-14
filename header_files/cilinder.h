#ifndef CILINDER_H
#define CILINDER_H

#include "vec3.h"
#include "matrix.h"
#include "object.h"
#include "plane.h"
#include <iostream>

class Cilinder : public Object {
public:
    Vec3 u;
    Plane basePlane, topPlane;
    double height, baseRadius;

    Cilinder() {
        this->type = "cilinder";
    }

    double intersection(Vec3 observer, Vec3 d) {
        Vec3 v = (observer - center) - u*((observer - center) ^ u);
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
        
        if (((intersectionPoint1 - center)^u) < height
        && ((intersectionPoint1 - center)^u) > 0
        && (t1 > 0 && t1 < closestT)) {
            closestT = t1;
        }
        
        if (((intersectionPoint2 - center)^u) < height
        && ((intersectionPoint2 - center)^u) > 0
        && (t2 > 0 && t2 < closestT)) {
            closestT = t2;
        }
        
        double tBasePlane = basePlane.intersection(observer, d);
        if(tBasePlane > 0) {
            Vec3 piBasePlane = observer + d * tBasePlane;
            
            if((piBasePlane - center).getLength() <= baseRadius
            && (tBasePlane < closestT)){
                closestT = tBasePlane;
            }
        }

        double tTopPlane = topPlane.intersection(observer, d);
        if(tTopPlane > 0) {
            Vec3 piTopPlane = observer + d * tTopPlane;
            
            if((piTopPlane - (center + (u * height))).getLength() <= baseRadius
            && (tTopPlane < closestT)) {
                closestT = tTopPlane;
            }
        }

        return closestT;
    }

    Vec3 getNormal(Vec3 intersectionPoint, Vec3 d) {
        if(((intersectionPoint - basePlane.pPi) ^ u) < 0.001) return basePlane.normal;
        if(((intersectionPoint - topPlane.pPi) ^ (u * (-1))) < 0.001) return topPlane.normal / topPlane.normal.getLength();
       
        Vec3 a = intersectionPoint - this->center;
        Vec3 b = a - (this->u * (a ^ this->u));
        return b / b.getLength();
    }

    void transform(Matrix m, bool rotateAxis = true) override {
        Matrix centerMatrix = Vec3::vec3ToMatrix(this->center);
        Matrix transformedCenter = m * centerMatrix;
        this->center.setCoordinates(transformedCenter.getElementAt(0,0),
                                    transformedCenter.getElementAt(1,0),
                                    transformedCenter.getElementAt(2,0));

        
        Matrix normalMatrix = Vec3::vec3ToMatrix(this->u);
        normalMatrix.setElementAt(3, 0, 0);
        Matrix transformedNormal = m * normalMatrix;
        this->u.setCoordinates(transformedNormal.getElementAt(0,0),
                                    transformedNormal.getElementAt(1,0),
                                    transformedNormal.getElementAt(2,0));
        Vec3 normalUnit = this->u/this->u.getLength();
        this->u.setCoordinates(normalUnit.x, normalUnit.y, normalUnit.z);

        this->basePlane.pPi = this->center*1;
        this->basePlane.normal = this->u*(-1);
        this->topPlane.pPi = this->center + this->u*this->height;
        this->topPlane.normal = this->u*this->height;    
    }

    Vec3 getTextureColor(Vec3 intersectionPoint) override {
        double theta = atan2(intersectionPoint.x, intersectionPoint.z);
        double raw_u = theta / (2 * M_PI);
        double u1 = 1 - (raw_u + 0.5);
        double v1 = abs(fmod(this->image_h/2 + intersectionPoint.y, 1));

        int u = u1 * this->image_w;
        int v = v1 * this->image_h;
        
        const size_t RGB = 3;
        size_t index = RGB * (v * this->image_w + u);

        Vec3 rgbValues(static_cast<int>(this->image[index + 0]),
                        static_cast<int>(this->image[index + 1]),
                        static_cast<int>(this->image[index + 2]));

        return rgbValues;
    }

};

#endif