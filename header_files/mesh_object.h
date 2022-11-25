#ifndef MESH_OBJECT_H
#define MESH_OBJECT_H

#include "vec3.h"
#include "matrix.h"
#include "object.h"
#include "plane.h"
#include "face.h"
#include <map>
#include <iostream>

class MeshObject : public Object {
public:
    Vec3 normal;
    std::vector<Vec3*> vertices;
    std::vector<Face*> faces;

    double intersection(Vec3 observer, Vec3 direction) {
        double closestT = std::numeric_limits<double>::infinity();

        for(auto face : faces) {
            Vec3 n = face->getNormal();

            double t = face->intersection(observer, direction);

            if(t > 0 && t < closestT) {
                closestT = t;
                Vec3 n = face->getNormal();
                this->normal.setCoordinates(n.x, n.y, n.z);
            }
        }

        return closestT;
    }

    Vec3 getNormal(Vec3 intersectionPoint, Vec3 d) { return this->normal; }

     void translate(double tx, double ty, double tz) override {
        Matrix t = Matrix::identity(4, 4);
        t.setElementAt(0, 3, tx);
        t.setElementAt(1, 3, ty);
        t.setElementAt(2, 3, tz);

        for(Vec3 *&v : this->vertices) {
            Matrix centerMatrix = Vec3::vec3ToMatrix(*v);
            Matrix rotatedCenter = t * centerMatrix;
            v->setCoordinates(rotatedCenter.getElementAt(0,0), rotatedCenter.getElementAt(1,0), rotatedCenter.getElementAt(2,0));
        }

        Matrix centerMatrix = Vec3::vec3ToMatrix(center);
        Matrix translatedCenter = t * centerMatrix;
        this->center.setCoordinates(translatedCenter.getElementAt(0,0), translatedCenter.getElementAt(1,0), translatedCenter.getElementAt(2,0));
    }

    void rotateX(double angle) override {
        double radianAngle = angle * (M_PI/180);
        Matrix r = Matrix::identity(4, 4);
        r.setElementAt(1, 1, cos(radianAngle));
        r.setElementAt(1, 2, -sin(radianAngle));
        r.setElementAt(2, 1, sin(radianAngle));
        r.setElementAt(2, 2, cos(radianAngle));

        for(Vec3 *&v : this->vertices) {
            Matrix centerMatrix = Vec3::vec3ToMatrix(*v);
            Matrix rotatedCenter = r * centerMatrix;
            v->setCoordinates(rotatedCenter.getElementAt(0,0), rotatedCenter.getElementAt(1,0), rotatedCenter.getElementAt(2,0));
        }

        Matrix centerMatrix = Vec3::vec3ToMatrix(center);
        Matrix rotatedCenter = r * centerMatrix;
        this->center = Vec3(rotatedCenter.getElementAt(0,0), rotatedCenter.getElementAt(1,0), rotatedCenter.getElementAt(2,0));
    }

    void rotateY(double angle) override {
        double radianAngle = angle * (M_PI/180);
        Matrix r = Matrix::identity(4, 4);
        r.setElementAt(0, 0, cos(radianAngle));
        r.setElementAt(0, 2, sin(radianAngle));
        r.setElementAt(2, 0, -sin(radianAngle));
        r.setElementAt(2, 2, cos(radianAngle));

        for(Vec3 *&v : this->vertices) {
            Matrix centerMatrix = Vec3::vec3ToMatrix(*v);
            Matrix rotatedCenter = r * centerMatrix;
            v->setCoordinates(rotatedCenter.getElementAt(0,0), rotatedCenter.getElementAt(1,0), rotatedCenter.getElementAt(2,0));
        }

        Matrix centerMatrix = Vec3::vec3ToMatrix(center);
        Matrix rotatedCenter = r * centerMatrix;
        this->center = Vec3(rotatedCenter.getElementAt(0,0), rotatedCenter.getElementAt(1,0), rotatedCenter.getElementAt(2,0));
    
    }

    void rotateZ(double angle) override {
        double radianAngle = angle * (M_PI/180);
        Matrix r = Matrix::identity(4, 4);
        r.setElementAt(0, 0, cos(radianAngle));
        r.setElementAt(0, 1, -sin(radianAngle));
        r.setElementAt(1, 0, sin(radianAngle));
        r.setElementAt(1, 1, cos(radianAngle));

        for(Vec3 *&v : this->vertices) {
            Matrix centerMatrix = Vec3::vec3ToMatrix(*v);
            Matrix rotatedCenter = r * centerMatrix;
            v->setCoordinates(rotatedCenter.getElementAt(0,0), rotatedCenter.getElementAt(1,0), rotatedCenter.getElementAt(2,0));
        }
        
        Matrix centerMatrix = Vec3::vec3ToMatrix(center);
        Matrix rotatedCenter = r * centerMatrix;
        this->center.setCoordinates(rotatedCenter.getElementAt(0,0), rotatedCenter.getElementAt(1,0), rotatedCenter.getElementAt(2,0));
    
    }

    void transform(Matrix m) override {
        for(Vec3 *&v : this->vertices) {
            Matrix vertexMatrix = Vec3::vec3ToMatrix(*v);
            Matrix transformedVertex = m * vertexMatrix;
            v->setCoordinates(transformedVertex.getElementAt(0,0),
                            transformedVertex.getElementAt(1,0),
                            transformedVertex.getElementAt(2,0));
        }
        
        Matrix centerMatrix = Vec3::vec3ToMatrix(this->center);
        Matrix transformedCenter = m * centerMatrix;
        this->center.setCoordinates(transformedCenter.getElementAt(0,0),
                                    transformedCenter.getElementAt(1,0),
                                    transformedCenter.getElementAt(2,0));
    }

};

#endif