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
    std::vector<Light*> complex_objects_lights;
    Vec3 eye, lookAt, viewUp;
    bool isOrtho;
    bool isTransformed;

    Vec3 applyWt(Vec3 v, bool isWc) {
        if(!isTransformed) return v;

        Vec3 newV(v.x, v.y, v.z);
        Vec3 kc = (eye - lookAt)/(eye - lookAt).getLength();
        Vec3 i = (viewUp - eye).cross(kc);
        Vec3 ic = i/i.getLength();
        Vec3 jc = kc.cross(ic);
        Matrix wt(4, 4);

        if(isWc) {
            wt = Matrix(4, 4, std::vector<double> {ic.x, ic.y, ic.z, -(ic ^ eye),
                                            jc.x, jc.y, jc.z, -(jc ^ eye),
                                            kc.x, kc.y, kc.z, -(kc ^ eye),
                                            0, 0, 0, 1});
        }else{
            wt = Matrix(4, 4, std::vector<double>{ic.x, jc.x, kc.x, eye.x,
                                            ic.y, jc.y, kc.y, eye.y,
                                            ic.z, jc.z, kc.z, eye.z,
                                            0, 0, 0, 1});
        }

        Matrix vMatrix = Vec3::vec3ToMatrix(newV);
        Matrix transformedV = wt * vMatrix;
        newV.setCoordinates(transformedV.getElementAt(0,0),
                                    transformedV.getElementAt(1,0),
                                    transformedV.getElementAt(2,0));
        
        return newV;
    }

    void applyWorldToCamera(Vec3 eye, Vec3 lookAt, Vec3 viewUp) {
        this->isTransformed = true;
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
        this->isTransformed = false;
    }

    
};

#endif