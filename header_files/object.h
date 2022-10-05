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

    virtual std::vector<double> intersection(Vec3 observer, Vec3 view) = 0;

    virtual Vec3 getNormal(Vec3 intersectionPoint) = 0;

    bool checkShadow(Vec3 position, Vec3 view, std::vector<Object*> objects) {
        double closestTShadow = std::numeric_limits<double>::infinity();
        Object* closestObjectShadow = nullptr;
        
        for(auto object : objects) {
            std::vector<double> t = object->intersection(position, view);

            if(t.size() == 0 || object->type == "plane") continue;

            double t1 = t.at(0);
            double t2 = t.at(1);

            if(t1 > 0.001 && t1 < closestTShadow) {
                closestTShadow = t1;
                closestObjectShadow = object;
            }

            if(t2 > 0.001 && t2 < closestTShadow) {
                closestTShadow = t2;
                closestObjectShadow = object;
            }
            
        }

        return closestObjectShadow != nullptr;
    }

    Vec3 computeLighting(Vec3 intersectionPoint,
                        Vec3 direction,
                        std::vector<Light> lights,
                        std::vector<Object*> objects) {
        Vec3 normal = getNormal(intersectionPoint);
        Vec3 v = direction / -direction.getLength();
        Vec3 totalLighting;
        int lightsSize = lights.size();

        for(int i = 0; i < lightsSize; i++) {
            Light light = lights.at(i);

            if(light.type == "ambient") {
                Vec3 iA = light.intensity % ka;
                totalLighting = totalLighting + iA;
                continue;
            }

            if(checkShadow(intersectionPoint, light.position, objects)) continue;

            Vec3 pf_sub_pi = light.position - intersectionPoint; 
            Vec3 l = pf_sub_pi / pf_sub_pi.getLength();
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