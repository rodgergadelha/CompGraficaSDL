#ifndef PLANE_H
#define PLANE_H

#include "vec3.h"
#include "matrix.h"
#include "object.h"
#include <vector>


class Plane : public Object{
public:
    Vec3 pPi, normal;

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

    Vec3 getTextureColor(int row, int column, Vec3 intersectionPoint) override {
        int u = column % this->image_h;
        int v = row % this->image_w;

        const size_t RGB = 3;
        size_t index = RGB * (v * this->image_w + u);

        Vec3 rgbValues(static_cast<int>(this->image[index + 0]),
                        static_cast<int>(this->image[index + 1]),
                        static_cast<int>(this->image[index + 2]));

        return rgbValues;
    }
};

#endif