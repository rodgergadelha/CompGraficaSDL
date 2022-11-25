#ifndef WORLD_H
#define WORLD_H

#include "window.h"
#include "object.h"
#include "light.h"
#include <vector>
#include <tuple>
#include <limits>

class World {
public:
    Window window;
    std::vector<Object*> objects;
    std::vector<Light*> lights;
    Vec3 eye, lookAt, viewUp;

    void applyWorldToCamera(Vec3 eye, Vec3 lookAt, Vec3 viewUp) {
        this->eye = eye;
        this->lookAt = lookAt;
        this->viewUp = viewUp;

        Vec3 kc = (eye - lookAt)/(eye - lookAt).getLength();
        Vec3 i = (viewUp - eye).cross(kc);
        Vec3 ic = i/i.getLength();
        Vec3 jc = kc.cross(ic);
        Matrix wtc(4, 4, std::vector<double> {ic.x, ic.y, ic.z, -(ic ^ eye),
                                            jc.x, jc.y, jc.z, -(jc ^ eye),
                                            kc.x, kc.y, kc.z, -(kc ^ eye),
                                            0, 0, 0, 1});
        
        for(auto object : this->objects) {
            object->transform(wtc);
        }

        for(auto light : this->lights) {
            light->transform(wtc);
        }

    }

    void applyCameraToWorld() {
        Vec3 kc = (eye - lookAt)/(eye - lookAt).getLength();
        Vec3 i = (viewUp - eye).cross(kc);
        Vec3 ic = i/i.getLength();
        Vec3 jc = kc.cross(ic);
        Matrix wtc(4, 4, std::vector<double>{ic.x, jc.x, kc.x, eye.x,
                                            ic.y, jc.y, kc.y, eye.y,
                                            ic.z, jc.z, kc.z, eye.z,
                                            0, 0, 0, 1});
        
        for(auto object : this->objects) {
            object->transform(wtc);
        }

        for(auto light : this->lights) {
            light->transform(wtc);
        }

        this->eye.setCoordinates(0, 0, 0);
        this->lookAt.setCoordinates(0, 0, 0);
        this->viewUp.setCoordinates(0, 0, 0);

    }

    
};

#endif