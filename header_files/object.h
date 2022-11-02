#include "vec3.h"
#include "light.h"
#include <string>
#include <vector>

#ifndef OBJECT_H
#define OBJECT_H

class Object {
public:
    Vec3 color, kd, ke, ka;
    double shininess;
    std::string type;

    virtual double intersection(Vec3 observer, Vec3 d) = 0;

    virtual Vec3 getNormal(Vec3 intersectionPoint, Vec3 d) = 0;

    virtual void translate(double tx, double ty, double tz) = 0;

    virtual void rotateX(double angle) = 0;

    virtual void rotateY(double angle) = 0;

    virtual void rotateZ(double angle) = 0;

    bool checkShadow(Vec3 position, Vec3 pf_sub_pi, std::vector<Object*> objects) {
        double closestTShadow = std::numeric_limits<double>::infinity();
        Object* closestObjectShadow = nullptr;
        Vec3 l = pf_sub_pi / pf_sub_pi.getLength();
        
        for(auto object : objects) {
            double t = object->intersection(position, l);

            if(object == this || t <= 0.001 || object->type == "plane") continue;

            if(t < closestTShadow && t < pf_sub_pi.getLength()) {
                closestTShadow = t;
                closestObjectShadow = object;
            }
        }

        return closestObjectShadow != nullptr;
    }

    Vec3 computeLighting(Vec3 intersectionPoint,
                        Vec3 d,
                        std::vector<Light> lights,
                        std::vector<Object*> objects) {
        Vec3 normal = getNormal(intersectionPoint, d);
        Vec3 v = d / -d.getLength();
        Vec3 totalLighting;
        int lightsSize = lights.size();

        for(int i = 0; i < lightsSize; i++) {
            Light light = lights.at(i);

            if(light.type == "ambient") {
                Vec3 iA = light.intensity % ka;
                totalLighting = totalLighting + iA;
                continue;
            }

            Vec3 pf_sub_pi = light.position - intersectionPoint; 
            Vec3 l = pf_sub_pi / pf_sub_pi.getLength();

            if(checkShadow(intersectionPoint, pf_sub_pi, objects)) continue;

            Vec3 r = (normal * (2 * (normal ^ l))) - l;

            double fd = std::max(0.0, normal ^ l);
            double fe = std::max(0.0, r ^ v);

            Vec3 iD = (light.intensity % kd) * fd;
            Vec3 iE = (light.intensity % ke) * pow(fe, shininess);
            totalLighting = totalLighting + (iE + iD);
        }
        
        return totalLighting;
    }

};

#endif