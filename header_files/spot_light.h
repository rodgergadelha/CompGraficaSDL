#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "light.h"
#include <cmath>

class SpotLight : public Light {
public:
    Vec3 spotDirection;
    double spotExponent, cutoff;

    SpotLight(Vec3 position, Vec3 spotPoint, double spotExponent, double cutoff) {
        this->position = position;
        this->cutoff = cutoff * M_PI/180;
        this->spotDirection = spotPoint - position;
        this->spotExponent = spotExponent;
    }

    std::string getType() {return "spot";}

    Vec3 getIntensity(Vec3 intersectionPoint, Vec3 d, Vec3 normal, Object* object) override {
        Vec3 pf_sub_pi = this->position - intersectionPoint;
        Vec3 v = d / -d.getLength();
        Vec3 l = pf_sub_pi / pf_sub_pi.getLength();
        Vec3 r = (normal * (2 * (normal ^ l))) - l;

        double fd = std::max(0.0, normal ^ l);
        double fe = std::max(0.0, r ^ v);

        Vec3 iD = (this->intensity % object->kd) * fd;
        Vec3 iE = (this->intensity % object->ke) * pow(fe, object->shininess);

        Vec3 unitSpotDirection = this->spotDirection / this->spotDirection.getLength();
        double cosSpotDir = l ^ (unitSpotDirection * (-1));

        if(cosSpotDir < cos(cutoff)) return Vec3();
        
        return (iE + iD) * pow(cosSpotDir, spotExponent);
    }

    void transform(Matrix m) {
        Matrix positionMatrix = Vec3::vec3ToMatrix(this->position);
        Matrix transformedPosition = m * positionMatrix;
        this->position.setCoordinates(transformedPosition.getElementAt(0,0),
                                    transformedPosition.getElementAt(1,0),
                                    transformedPosition.getElementAt(2,0));

        Matrix normalMatrix = Vec3::vec3ToMatrix(this->spotDirection);
        normalMatrix.setElementAt(3, 0, 0);
        Matrix transformedNormal = m * normalMatrix;
        this->spotDirection.setCoordinates(transformedNormal.getElementAt(0,0),
                                    transformedNormal.getElementAt(1,0),
                                    transformedNormal.getElementAt(2,0));
        this->spotDirection = this->spotDirection / this->spotDirection.getLength();
    }
};

#endif