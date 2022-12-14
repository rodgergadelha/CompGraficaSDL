#ifndef BOOK_H
#define BOOK_H

#include "vec3.h"
#include "matrix.h"
#include "complex_object.h"
#include "cube.h"
#include "cilinder.h"
#include "world.h"
#include <vector>
#include <iostream>

class Book : public ComplexObject {
public:
    
    Book(Vec3 center, double width, double height, double depth) {
        this->type = "book";
        this->kd.setCoordinates(0.9, 0.9, 0.9);
        this->ke.setCoordinates(0.6, 0.6, 0.6);
        this->ka.setCoordinates(0.8, 0.8, 0.8);
        this->shininess = 10;
        this->center = center;
        
        Cube *book = new Cube(1, Vec3(0, 0, 0));
        book->scale(width, height, depth);
        book->translate(center.x, center.y, center.z);

        for(int i = 0; i < 6; i++) {
            book->setFaceColor(i, Vec3(255, 255, 255));
        }

        this->components = std::vector<Object*> {book};

        cluster = new Sphere();
        cluster->center.setCoordinates(this->center.x, this->center.y, this->center.z);
        cluster->radius = std::max(width, std::max(height, depth)) / 1.5;
    }
    
};

#endif