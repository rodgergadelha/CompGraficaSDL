#ifndef FACE_H
#define FACE_H

#include "vec3.h"
#include "matrix.h"
#include "object.h"
#include "plane.h"
#include <vector>
#include <map>
#include <iostream>

class Face {
public:
    Vec3 *p1, *p2, *p3, color;
    std::vector<unsigned char> image;
    int image_w, image_h;

    Face(Vec3 *p1, Vec3 *p2, Vec3 *p3, Vec3 color = Vec3(255, 0, 0)) {
        this->p1 = p1;
        this->p2 = p2;
        this->p3 = p3;
        this->color = color;
    }

    void loadImage(const std::string& filename) {
        int n;
        unsigned char* data = stbi_load(filename.c_str(), &this->image_w, &this->image_h, &n, 3);
        
        if (data != nullptr) {
            this->image = std::vector<unsigned char>(data, data + this->image_w * this->image_h * 3);
        }
        
        stbi_image_free(data);

        if (data == nullptr) std::cout << "Falha ao carregar imagem.\n";
    }

    Vec3 getTextureColor(int row, int column, Vec3 intersectionPoint) {
        int u = column % this->image_h;
        int v = row % this->image_w;

        const size_t RGB = 3;
        size_t index = RGB * (v * this->image_w + u);

        Vec3 rgbValues(static_cast<int>(this->image[index + 0]),
                        static_cast<int>(this->image[index + 1]),
                        static_cast<int>(this->image[index + 2]));

        return rgbValues;
    }

    Vec3 getColor(int row, int column, Vec3 intersectionPoint) {
        if(this->image.size() > 0) return this->getTextureColor(row, column, intersectionPoint);
        return this->color;
    }

    bool contains(Vec3 point) {
        Vec3 normal = getNormal();
        Vec3 r1 = *p2 - *p1;
        Vec3 r2 = *p3 - *p1;
        double area = (r1.cross(r2)) ^ normal;
        double c1 = (((*p1 - point).cross(*p2 - point)) ^ normal) / area;
        double c2 = (((*p3 - point).cross(*p1 - point)) ^ normal) / area;
        double c3 = (((*p2 - point).cross(*p3 - point)) ^ normal) / area;

        return (c1 > 0 - 0.0001) && (c2 > 0 - 0.0001) && (c3 > 0 - 0.0001);
    }

    double intersection(Vec3 observer, Vec3 direction) {
        Vec3 n = getNormal();

        if((direction ^ n) == 0) return -1;

        double t = -((observer - *p1) ^ n) / (direction ^ n);
        Vec3 intersectionPoint = observer + direction*t;

        if(contains(intersectionPoint)) return t;
        return -1;
    }

    Vec3 getNormal() {
        Vec3 r1 = *p2 - *p1;
        Vec3 r2 = *p3 - *p1;
        Vec3 n = r1.cross(r2);
        return n / (n.getLength());
    }
};

#endif