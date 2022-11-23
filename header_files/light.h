#ifndef LIGHT_H
#define LIGHT_H

#include <vector>
#include "vec3.h"
#include "matrix.h"

class Object;

class Light {
public:
    Vec3 intensity, position;

    virtual std::string getType() = 0;

    virtual Vec3 getIntensity(Vec3 intersectionPoint, Vec3 d, Vec3 normal, Object* object) = 0;

    virtual Vec3 getL(Vec3 intersectionPoint) {return this->position - intersectionPoint;}

    virtual void transform(Matrix m) {
        Matrix positionMatrix = Vec3::vec3ToMatrix(this->position);
        Matrix transformedPosition = m * positionMatrix;
        this->position.setCoordinates(transformedPosition.getElementAt(0,0),
                                    transformedPosition.getElementAt(1,0),
                                    transformedPosition.getElementAt(2,0));
    }
};

#endif