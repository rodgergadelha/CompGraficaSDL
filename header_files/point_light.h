#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "light.h"

class Object;

class PointLight : public Light {
public:

    std::string getType() {return "point";}

    Vec3 getIntensity(Vec3 intersectionPoint, Vec3 d, Vec3 normal, Object* object) { 
        Vec3 pf_sub_pi = this->position - intersectionPoint;
        Vec3 v = d / -d.getLength();
        Vec3 l = pf_sub_pi / pf_sub_pi.getLength();
        Vec3 r = (normal * (2 * (normal ^ l))) - l;

        double fd = std::max(0.0, normal ^ l);
        double fe = std::max(0.0, r ^ v);

        Vec3 iD = (this->intensity % object->kd) * fd;
        Vec3 iE = (this->intensity % object->ke) * pow(fe, object->shininess);
        
        return (iE + iD);
    }

    void transform(Matrix m) {
        Matrix positionMatrix = Vec3::vec3ToMatrix(this->position);
        Matrix transformedPosition = m * positionMatrix;
        this->position.setCoordinates(transformedPosition.getElementAt(0,0),
                                    transformedPosition.getElementAt(1,0),
                                    transformedPosition.getElementAt(2,0));
    }

};

#endif