#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"
#include "matrix.h"
#include <vector>
#include <cmath>
#include <iostream>

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

    void translate(double tx, double ty, double tz) {
        Matrix t = Matrix::identity(4, 4);
        t.setElementAt(0, 3, tx);
        t.setElementAt(1, 3, ty);
        t.setElementAt(2, 3, tz);
        
        Matrix centerMatrix = Vec3::vec3ToMatrix(center);
        Matrix translatedCenter = t * centerMatrix;
        this->center.setCoordinates(translatedCenter.getElementAt(0,0), translatedCenter.getElementAt(1,0), translatedCenter.getElementAt(2,0));
    }

    void rotateX(double angle) {
        double radianAngle = angle * (M_PI/180);
        Matrix r = Matrix::identity(4, 4);
        r.setElementAt(1, 1, cos(radianAngle));
        r.setElementAt(1, 2, -sin(radianAngle));
        r.setElementAt(2, 1, sin(radianAngle));
        r.setElementAt(2, 2, cos(radianAngle));
        
        Matrix centerMatrix = Vec3::vec3ToMatrix(center);
        Matrix rotatedCenter = r * centerMatrix;
        this->center.setCoordinates(rotatedCenter.getElementAt(0,0), rotatedCenter.getElementAt(1,0), rotatedCenter.getElementAt(2,0));
    }

    void rotateY(double angle) {
        double radianAngle = angle * (M_PI/180);
        Matrix r = Matrix::identity(4, 4);
        r.setElementAt(0, 0, cos(radianAngle));
        r.setElementAt(0, 2, sin(radianAngle));
        r.setElementAt(1, 0, -sin(radianAngle));
        r.setElementAt(1, 2, cos(radianAngle));
        
        Matrix centerMatrix = Vec3::vec3ToMatrix(center);
        Matrix rotatedCenter = r * centerMatrix;
        this->center.setCoordinates(rotatedCenter.getElementAt(0,0), rotatedCenter.getElementAt(1,0), rotatedCenter.getElementAt(2,0));
    }

    void rotateZ(double angle) {
        double radianAngle = angle * (M_PI/180);
        Matrix r = Matrix::identity(4, 4);
        r.setElementAt(0, 0, cos(radianAngle));
        r.setElementAt(0, 1, -sin(radianAngle));
        r.setElementAt(1, 0, sin(radianAngle));
        r.setElementAt(1, 1, cos(radianAngle));
        
        Matrix centerMatrix = Vec3::vec3ToMatrix(center);
        Matrix rotatedCenter = r * centerMatrix;
        this->center.setCoordinates(rotatedCenter.getElementAt(0,0), rotatedCenter.getElementAt(1,0), rotatedCenter.getElementAt(2,0));
    }

};

#endif