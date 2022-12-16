#ifndef SHELF_H
#define SHELF_H

#include "vec3.h"
#include "matrix.h"
#include "cube.h"
#include "complex_object.h"
#include <vector>
#include <iostream>

class Shelf : public ComplexObject {
public:
   
    Shelf(Vec3 center, double width, double height, double depth) {
        this->type = "shelf";
        this->center = center;
        
        Cube *cover = new Cube(1, Vec3(0, 0, 0));
        cover->scale(width, height, depth);
        cover->translate(center.x, center.y, center.z);
        cover->loadImageAllFaces("textures/books5.jpg");

        Cube *estante_baixo = new Cube(1, Vec3(0, 0, 0));
        estante_baixo->scale(width + 7, 3.5, depth + 5);
        estante_baixo->translate(center.x, center.y - height/2, center.z + 2.5);
        estante_baixo->loadImageAllFaces("textures/wood.jpg");
        
        Cube *estante_cima= new Cube(1, Vec3(0, 0, 0));
        estante_cima->scale(width + 7, 3.5, depth + 5);
        estante_cima->translate(center.x, center.y + height/2, center.z + 2.5);
        estante_cima->loadImageAllFaces("textures/wood.jpg");

        Cube *estante_direita= new Cube(1, Vec3(0, 0, 0));
        estante_direita->scale(3.5, height, depth + 5);
        estante_direita->translate(center.x + width/2 + 1.75, center.y, center.z + 2.5);
        estante_direita->loadImageAllFaces("textures/wood.jpg");

        Cube *estante_esquerda= new Cube(1, Vec3(0, 0, 0));
        estante_esquerda->scale(3.5, height, depth + 5);
        estante_esquerda->translate(center.x - width/2 - 1.75, center.y, center.z + 2.5);
        estante_esquerda->loadImageAllFaces("textures/wood.jpg");

        this->components = std::vector<Object*> {cover, estante_baixo, estante_cima, estante_direita, estante_esquerda};

        cluster = new Sphere();
        cluster->center.setCoordinates(this->center.x, this->center.y, this->center.z);
        cluster->radius = std::max(width, std::max(height, depth))/ 1.5;
    }
    
};


#endif