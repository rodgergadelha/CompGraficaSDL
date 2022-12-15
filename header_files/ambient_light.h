#ifndef AMBIENT_LIGHT_H
#define AMBIENT_LIGHT_H

#include "light.h"

class AmbientLight : public Light {
public:
    AmbientLight() {this->position = Vec3();}

    std::string getType() {return "ambient";}

    Vec3 getL(Vec3 intersectionPoint) override {return Vec3();}

    Vec3 getIntensity(Vec3 intersectionPoint, Vec3 d, Vec3 normal, Object* object) { 
        return this->intensity % object->getK("ka");
    }

    void transform(Matrix m) {return;}
};

#endif