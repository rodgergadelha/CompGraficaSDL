#ifndef PLANE_H
#define PLANE_H

#include "vec3.h"
#include "matrix.h"
#include "object.h"
#include <vector>


class Plane : public Object{
public:
    Vec3 pPi, normal, worldNormal;

    Plane() {
        this->type = "plane";
    }

    double intersection(Vec3 observer, Vec3 d) {
        Vec3 w = observer - pPi;

        if((d ^ normal) == 0) return -1;
        
        double ti = -(w ^ normal)/(d ^ normal);
        if(ti > 0) return ti;

        return -1;
    }

    Vec3 getNormal(Vec3 intersectionPoint, Vec3 d) {
        return this->normal;
    }

    void transform(Matrix m) override {
        Matrix pPiMatrix = Vec3::vec3ToMatrix(this->pPi);
        Matrix transformedpPi = m * pPiMatrix;
        this->pPi.setCoordinates(transformedpPi.getElementAt(0,0),
                                    transformedpPi.getElementAt(1,0),
                                    transformedpPi.getElementAt(2,0));

        Matrix normalMatrix = Vec3::vec3ToMatrix(this->normal);
        normalMatrix.setElementAt(3, 0, 0);
        Matrix transformedNormal = m * normalMatrix;
        this->normal.setCoordinates(transformedNormal.getElementAt(0,0),
                                    transformedNormal.getElementAt(1,0),
                                    transformedNormal.getElementAt(2,0));
        Vec3 normalUnit = this->normal/this->normal.getLength();
        this->normal.setCoordinates(normalUnit.x, normalUnit.y, normalUnit.z);

    }

    Vec3 getTextureColor(Vec3 intersectionPoint) override {
        Vec3 u0(this->worldNormal.y, -this->worldNormal.x, 0);
        if(u0.x == 0 && u0.y == 0) u0.setCoordinates(this->worldNormal.z, 0, 0);
        u0 = u0 / u0.getLength();
        Vec3 v0 = this->worldNormal.cross(u0);
        v0 = v0 / v0.getLength();
        double u1 = u0 ^ intersectionPoint;
        double v1 = v0 ^ intersectionPoint;
       
        int u = abs(fmod(u1 - this->image_w/2, this->image_w));
        int v = this->image_h - abs(fmod(v1 + this->image_h/2, this->image_h));
        
        const size_t RGB = 3;
        size_t index = RGB * (v * this->image_w + u);

        Vec3 rgbValues(static_cast<int>(this->image[index + 0]),
                        static_cast<int>(this->image[index + 1]),
                        static_cast<int>(this->image[index + 2]));

        return rgbValues;
    }
};

#endif