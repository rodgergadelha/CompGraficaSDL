#ifndef POSITIONED_DIRECTIONAL_LIGHT_H
#define POSITIONED_DIRECTIONAL_LIGHT_H

#include "directional_light.h"
#include <limits>

class PositionedDirectionalLight : public DirectionalLight {
public:
    Object *emiter;

    PositionedDirectionalLight(Object *emiter, Vec3 direction) : DirectionalLight(direction) {
        this->emiter = emiter;
    }

    std::string getType() {return "pos directional";}

    Vec3 getIntensity(Vec3 intersectionPoint, Vec3 d, Vec3 normal, Object* object) {
        if(emiter == object) return Vec3(0, 0, 0);
        
        double t = emiter->intersection(intersectionPoint, this->direction);
        double inf = std::numeric_limits<double>::infinity();
        if(t < 0 || t == inf) return Vec3(0, 0, 0);

        Vec3 v = d / -d.getLength();
        Vec3 l = this->direction;
        Vec3 r = (normal * (2 * (normal ^ l))) - l;

        double fd = std::max(0.0, normal ^ l);
        double fe = std::max(0.0, r ^ v);

        Vec3 iD = (this->intensity % object->getK("kd")) * fd;
        Vec3 iE = (this->intensity % object->getK("ke")) * pow(fe, object->getShininess());
        
        return (iE + iD);
    }

};

#endif