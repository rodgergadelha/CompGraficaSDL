#include "vec3.h"
#include <string>

#ifndef LIGHT_H
#define LIGHT_H


class Light {
public:
    Vec3 position, intensity;
    std::string type;
};

#endif