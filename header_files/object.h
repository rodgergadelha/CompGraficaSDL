#ifndef OBJECT_H
#define OBJECT_H

#include "vec3.h"
#include <string>
#include <vector>
#include <iostream>

extern "C" {
    #define STB_IMAGE_IMPLEMENTATION
    #include "stb_image.h"
}

#define M_PI 3.14159265358979323846

class Object {
public:
    Vec3 center, color, kd, ke, ka;
    double shininess;
    std::string type;
    std::vector<unsigned char> image;
    int image_w, image_h;

    virtual bool isComplex() {return false;}

    virtual double intersection(Vec3 observer, Vec3 d) = 0;

    virtual Vec3 getTextureColor(Vec3 intersectionPoint) {return Vec3(0, 0, 0);}

    virtual Vec3 getColor(Vec3 intersectionPoint) {
        if(this->image.size() > 0) return getTextureColor(intersectionPoint);
        return this->color;
    }

    virtual Vec3 getNormal(Vec3 intersectionPoint, Vec3 d) = 0;

    virtual void translate(double tx, double ty, double tz) {
        Matrix t = Matrix(4, 4, std::vector<double> {
            1, 0, 0, tx,
            0, 1, 0, ty,
            0, 0, 1, tz,
            0, 0, 0, 1
        });
        transform(t);
    }

    virtual void rotateX(double angle) {
        double radianAngle = angle * (M_PI/180);
        Matrix r = Matrix::identity(4, 4);
        r.setElementAt(1, 1, cos(radianAngle));
        r.setElementAt(1, 2, -sin(radianAngle));
        r.setElementAt(2, 1, sin(radianAngle));
        r.setElementAt(2, 2, cos(radianAngle));

        transform(r);
    }

    virtual void rotateY(double angle) {
        double radianAngle = angle * (M_PI/180);
        Matrix r = Matrix::identity(4, 4);
        r.setElementAt(0, 0, cos(radianAngle));
        r.setElementAt(0, 2, sin(radianAngle));
        r.setElementAt(2, 0, -sin(radianAngle));
        r.setElementAt(2, 2, cos(radianAngle));
        
        transform(r);
    }

    virtual void rotateZ(double angle) {
        double radianAngle = angle * (M_PI/180);
        Matrix r = Matrix::identity(4, 4);
        r.setElementAt(0, 0, cos(radianAngle));
        r.setElementAt(0, 1, -sin(radianAngle));
        r.setElementAt(1, 0, sin(radianAngle));
        r.setElementAt(1, 1, cos(radianAngle));
        
        transform(r);
    }

    virtual void scale(double sx, double sy, double sz) {
        Matrix s(4, 4, std::vector<double> {sx, 0, 0, 0,
                                            0, sy, 0, 0,
                                            0, 0, sz, 0,
                                            0, 0, 0, 1});
        transform(s);
    }

    virtual void shearingYX(double angle) {
        double radianAngle = angle * (M_PI/180);
        Matrix s(4, 4, std::vector<double> {1, tan(radianAngle), 0, 0,
                                            0, 1, 0, 0,
                                            0, 0, 1, 0,
                                            0, 0, 0, 1});
        transform(s);
    }

    virtual void shearingXY(double angle) {
        double radianAngle = angle * (M_PI/180);
        Matrix s(4, 4, std::vector<double> {1, 0, 0, 0,
                                            tan(radianAngle), 1, 0, 0,
                                            0, 0, 1, 0,
                                            0, 0, 0, 1});
        transform(s);
    }

    virtual void shearingYZ(double angle) {
        double radianAngle = angle * (M_PI/180);
        Matrix s(4, 4, std::vector<double> {1, 0, 0, 0,
                                            0, 1, 0, 0,
                                            0, tan(radianAngle), 1, 0,
                                            0, 0, 0, 1});
        transform(s);
    }

    virtual void shearingZY(double angle) {
        double radianAngle = angle * (M_PI/180);
        Matrix s(4, 4, std::vector<double> {1, 0, 0, 0,
                                            0, 1, tan(radianAngle), 0,
                                            0, 0, 1, 0,
                                            0, 0, 0, 1});
        transform(s);
    }

    virtual void shearingXZ(double angle) {
        double radianAngle = angle * (M_PI/180);
        Matrix s(4, 4, std::vector<double> {1, 0, 0, 0,
                                            0, 1, 0, 0,
                                            tan(radianAngle), 0, 1, 0,
                                            0, 0, 0, 1});
        transform(s);
    }

    virtual void shearingZX(double angle) {
        double radianAngle = angle * (M_PI/180);
        Matrix s(4, 4, std::vector<double> {1, 0, tan(radianAngle), 0,
                                            0, 1, 0, 0,
                                            0, 0, 1, 0,
                                            0, 0, 0, 1});
        transform(s);
    }

    virtual void transform(Matrix m, bool rotateAxis = true) = 0;

    void loadImage(const std::string& filename) {
        int n;
        unsigned char* data = stbi_load(filename.c_str(), &this->image_w, &this->image_h, &n, 3);
        
        if (data != nullptr) {
            this->image = std::vector<unsigned char>(data, data + this->image_w * this->image_h * 3);
        } else {
            std::cout << "Falha ao carregar imagem.\n";
        }
        
        stbi_image_free(data);
    }

    virtual void setK(Vec3 k, std::string k_type) {
        if(k_type == "ka") this->ka.setCoordinates(k.x, k.y, k.z);
        else if(k_type == "kd") this->kd.setCoordinates(k.x, k.y, k.z);
        else if(k_type == "ke") this->ke.setCoordinates(k.x, k.y, k.z);
    }

    virtual Vec3 getK(std::string k_type) {
        if(k_type == "ka") return this->ka;
        else if(k_type == "kd") return this->kd;
        else if(k_type == "ke") return this->ke;
        
        return Vec3(0, 0, 0);
    }

    virtual void setShininess(double s) {
        this->shininess = s;
    }

    virtual double getShininess() {
        return this->shininess;
    }

};

#endif