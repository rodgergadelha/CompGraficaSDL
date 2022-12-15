#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "light.h"

class DirectionalLight : public Light {
public:
    Vec3 direction;

    DirectionalLight(Vec3 direction) {this->direction = direction/direction.getLength();}

    std::string getType() {return "directional";}

    Vec3 getL(Vec3 intersectionPoint) override {return this->direction;}

    Vec3 getIntensity(Vec3 intersectionPoint, Vec3 d, Vec3 normal, Object* object) {
        Vec3 v = d / -d.getLength();
        Vec3 l = this->direction;
        Vec3 r = (normal * (2 * (normal ^ l))) - l;

        double fd = std::max(0.0, normal ^ l);
        double fe = std::max(0.0, r ^ v);

        Vec3 iD = (this->intensity % object->getK("kd")) * fd;
        Vec3 iE = (this->intensity % object->getK("ke")) * pow(fe, object->getShininess());
        
        return (iE + iD);
    }

    void transform(Matrix m) {
        Matrix normalMatrix = Vec3::vec3ToMatrix(this->direction);
        normalMatrix.setElementAt(3, 0, 0);
        Matrix transformedNormal = m * normalMatrix;
        this->direction.setCoordinates(transformedNormal.getElementAt(0,0),
                                    transformedNormal.getElementAt(1,0),
                                    transformedNormal.getElementAt(2,0));
        Vec3 normalUnit = this->direction/this->direction.getLength();
        this->direction.setCoordinates(normalUnit.x, normalUnit.y, normalUnit.z);
    }

};

#endif