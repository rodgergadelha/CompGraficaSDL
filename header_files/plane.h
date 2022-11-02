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
        Vec3 direction = d - observer;

        if((direction ^ normal) == 0) return -1;
        
        double ti = -(w ^ normal)/(direction ^ normal);
        if(ti > 0) return ti;

        return -1;
    }

    Vec3 getNormal(Vec3 intersectionPoint, Vec3 d) {
        return normal;
    }

    void translate(double tx, double ty, double tz) {
        Matrix t = Matrix::identity(4, 4);
        t.setElementAt(0, 3, tx);
        t.setElementAt(1, 3, ty);
        t.setElementAt(2, 3, tz);
        
        Matrix pPiMatrix = Vec3::vec3ToMatrix(pPi);
        Matrix translatedCenter = t * pPiMatrix;
        this->pPi.setCoordinates(translatedCenter.getElementAt(0,0), translatedCenter.getElementAt(1,0), translatedCenter.getElementAt(2,0));
    }

    void rotateX(double angle) {
        double radianAngle = angle * (M_PI/180);
        Matrix r = Matrix::identity(4, 4);
        r.setElementAt(1, 1, cos(radianAngle));
        r.setElementAt(1, 2, -sin(radianAngle));
        r.setElementAt(2, 1, sin(radianAngle));
        r.setElementAt(2, 2, cos(radianAngle));
        
        Matrix centerMatrix = Vec3::vec3ToMatrix(pPi);
        Matrix rotatedCenter = r * centerMatrix;
        this->pPi.setCoordinates(rotatedCenter.getElementAt(0,0), rotatedCenter.getElementAt(1,0), rotatedCenter.getElementAt(2,0));
    }

    void rotateY(double angle) {
        double radianAngle = angle * (M_PI/180);
        Matrix r = Matrix::identity(4, 4);
        r.setElementAt(0, 0, cos(radianAngle));
        r.setElementAt(0, 2, sin(radianAngle));
        r.setElementAt(1, 0, -sin(radianAngle));
        r.setElementAt(1, 2, cos(radianAngle));
        
        Matrix centerMatrix = Vec3::vec3ToMatrix(pPi);
        Matrix rotatedCenter = r * centerMatrix;
        this->pPi.setCoordinates(rotatedCenter.getElementAt(0,0), rotatedCenter.getElementAt(1,0), rotatedCenter.getElementAt(2,0));
    }

    void rotateZ(double angle) {
        double radianAngle = angle * (M_PI/180);
        Matrix r = Matrix::identity(4, 4);
        r.setElementAt(0, 0, cos(radianAngle));
        r.setElementAt(0, 1, -sin(radianAngle));
        r.setElementAt(1, 0, sin(radianAngle));
        r.setElementAt(1, 1, cos(radianAngle));
        
        Matrix centerMatrix = Vec3::vec3ToMatrix(pPi);
        Matrix rotatedCenter = r * centerMatrix;
        this->pPi.setCoordinates(rotatedCenter.getElementAt(0,0), rotatedCenter.getElementAt(1,0), rotatedCenter.getElementAt(2,0));
    }

};

#endif