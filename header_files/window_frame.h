#ifndef WINDOW_FRAME_H
#define WINDOW_FRAME_H

#include "vec3.h"
#include "matrix.h"
#include "cube.h"
#include "positioned_directional_light.h"
#include "complex_object.h"
#include <vector>
#include <iostream>

class Frame : public ComplexObject {
public:
    PositionedDirectionalLight *light;
   
    Frame(Vec3 center, Vec3 light_direction, World *world, double width, double height, double depth) {
        this->type = "frame";
        this->center = center;
        this->kd.setCoordinates(0.9, 0.9, 0.9);
        this->ke.setCoordinates(0.6, 0.6, 0.6);
        this->ka.setCoordinates(0.8, 0.8, 0.8);
        this->shininess = 10;
        
        Cube *window = new Cube(1, Vec3(0, 0, 0));
        window->scale(width, height, depth);
        window->translate(center.x, center.y, center.z);

        Cube *frame_baixo = new Cube(1, Vec3(0, 0, 0));
        frame_baixo->scale(width + 7, 3.5, depth + 2);
        frame_baixo->translate(center.x, center.y - height/2, center.z + 1.5);
        frame_baixo->setAllFacesColors(Vec3(128, 128, 128));

        Cube *frame_cima= new Cube(1, Vec3(0, 0, 0));
        frame_cima->scale(width + 7, 3.5, depth + 2);
        frame_cima->translate(center.x, center.y + height/2, center.z + 1.5);
        frame_cima->setAllFacesColors(Vec3(128, 128, 128));

        Cube *frame_direita= new Cube(1, Vec3(0, 0, 0));
        frame_direita->scale(3.5, height, depth + 2);
        frame_direita->translate(center.x + width/2 + 1.75, center.y, center.z + 1.5);
        frame_direita->setAllFacesColors(Vec3(128, 128, 128));

        Cube *frame_meio= new Cube(1, Vec3(0, 0, 0));
        frame_meio->scale(2, height, depth + 2);
        frame_meio->translate(center.x, center.y, center.z + 1.5);
        frame_meio->setAllFacesColors(Vec3(128, 128, 128));

        Cube *frame_esquerda= new Cube(1, Vec3(0, 0, 0));
        frame_esquerda->scale(3.5, height, depth + 2);
        frame_esquerda->translate(center.x - width/2 - 1.75, center.y, center.z + 1.5);
        frame_esquerda->setAllFacesColors(Vec3(128, 128, 128));

        this->components = std::vector<Object*> {window, frame_baixo, frame_cima, frame_direita, frame_esquerda, frame_meio};

        this->light = new PositionedDirectionalLight(this, Vec3(0, 1, -1));
        light->intensity.setCoordinates(0.7, 0.7, 0.7);
        world->lights.push_back(this->light);

        cluster = new Sphere();
        cluster->center.setCoordinates(this->center.x, this->center.y, this->center.z);
        cluster->radius = std::max(width, std::max(height, depth));
    }

    void transform(Matrix m, bool rotateAxis = true) override {
        for(auto component : components) {
            component->transform(m);
        }
        
        light->transform(m);
        
        this->center.setCoordinates(components[0]->center.x, components[0]->center.y, components[0]->center.z);
        cluster->transform(m);
    }
    
};


#endif