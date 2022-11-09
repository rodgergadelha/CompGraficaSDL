#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include "matrix.h"

class Vec3 {
    public:
        double x, y, z, a;

        Vec3(double x = 0, double y = 0, double z = 0, double a = 1) {
            setCoordinates(x, y, z, a);
        }

        double getLength() {
            return sqrt(*this ^ *this);
        }

        void setCoordinates(double x = 0, double y = 0, double z = 0, double a = 1) {
            this->x = x;
            this->y = y;
            this->z = z;
            this->a = a;
        }

        // Função que calcula o produto escalar entre dois vetores de 3 coordenadas
        double operator ^ (Vec3 v) {
            return (x * v.x) + (y * v.y) + (z * v.z);
        }

        Vec3 operator + (Vec3 v) {
            Vec3 result(x + v.x, y + v.y, z + v.z, a + v.a);
            return result;
        }

        Vec3 operator - (Vec3 v) {
            Vec3 result(x - v.x, y - v.y, z - v.z, a - v.a);
            return result;
        }

        Vec3 operator * (double k) {
            Vec3 result(x * k, y * k, z * k, a * k);
            return result;
        }

        Vec3 operator / (double k) {
            Vec3 result(x / k, y / k, z / k, a / k);
            return result;
        }

        // Operação @
        Vec3 operator % (Vec3 v) {
            Vec3 result(x * v.x, y * v.y, z * v.z, a * v.a);
            return result;
        }

        // Produto vetorial
        Vec3 cross(Vec3 v) {
            Vec3 result((y * v.z) - (z * v.y), (z * v.x) - (x * v.z), (x * v.y) - (y * v.x));
            return result;
        }

        // static methods
        static Vec3 matrixToVec3(Matrix m) {
            Vec3 result(m.getElementAt(0,0), m.getElementAt(1,0), m.getElementAt(2,0), m.getElementAt(3,0));
            return result;
        }

        static Matrix vec3ToMatrix(Vec3 v) {
            Matrix result(4, 1);
            result.setElementAt(0, 0, v.x);
            result.setElementAt(1, 0, v.y);
            result.setElementAt(2, 0, v.z);
            result.setElementAt(3, 0, v.a);
            return result;
        }
};

#endif