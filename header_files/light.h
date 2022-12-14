#ifndef LIGHT_H
#define LIGHT_H

#include <vector>
#include "vec3.h"
#include "matrix.h"
#include "object.h"

class Light {
public:
    Vec3 intensity, position;

    virtual std::string getType() = 0;

    virtual Vec3 getIntensity(Vec3 intersectionPoint, Vec3 d, Vec3 normal, Object* object) = 0;

    virtual Vec3 getL(Vec3 intersectionPoint) {return this->position - intersectionPoint;}

    virtual void transform(Matrix m) = 0;
};

#endif