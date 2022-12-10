#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"
#include "matrix.h"
#include <vector>
#include <cmath>
#include <iostream>

class Sphere : public Object {
public:
    double radius;

    Sphere() {
        this->type = "sphere";
    }

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

    void transform(Matrix m) {
        Matrix centerMatrix = Vec3::vec3ToMatrix(this->center);
        Matrix transformedCenter = m * centerMatrix;
        this->center.setCoordinates(transformedCenter.getElementAt(0,0),
                                    transformedCenter.getElementAt(1,0),
                                    transformedCenter.getElementAt(2,0));
    }

    Vec3 getTextureColor(Vec3 intersectionPoint) override {
        double theta = atan2(intersectionPoint.x, intersectionPoint.z);
        double phi = acos(intersectionPoint.y * (M_PI / 180) / this->radius);
        double initialU = theta / (2 * M_PI);
        
        int u = (1 - (initialU + 0.5)) * this->image_w;
        int v = (1 - phi / M_PI) * this->image_h;

        const size_t RGB = 3;
        size_t index = RGB * (v * this->image_w + u);

        Vec3 rgbValues(static_cast<int>(this->image[index + 0]),
                        static_cast<int>(this->image[index + 1]),
                        static_cast<int>(this->image[index + 2]));

        return rgbValues;
    }

};

#endif