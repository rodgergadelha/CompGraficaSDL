#include <cmath>

#ifndef VEC3_H
#define VEC3_H

class Vec3 {
    public:
        double x, y, z;

        Vec3(double x = 0, double y = 0, double z = 0) {
            setCoordinates(x, y, z);
        }

        double getLength() {
            return sqrt(*this ^ *this);
        }

        void setCoordinates(double x, double y, double z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        // Função que calcula o produto escalar entre dois vetores de 3 coordenadas
        double operator ^ (Vec3 v) {
            return (x * v.x) + (y * v.y) + (z * v.z);
        }

        Vec3 operator + (Vec3 v) {
            Vec3 result(x + v.x, y + v.y, z + v.z);
            return result;
        }

        Vec3 operator - (Vec3 v) {
            Vec3 result(x - v.x, y - v.y, z - v.z);
            return result;
        }

        Vec3 operator * (double a) {
            Vec3 result(x * a, y * a, z * a);
            return result;
        }

        Vec3 operator / (double a) {
            Vec3 result(x / a, y / a, z / a);
            return result;
        }

        // Operação @
        Vec3 operator % (Vec3 v) {
            Vec3 result(x * v.x, y * v.y, z * v.z);
            return result;
        }


};

#endif