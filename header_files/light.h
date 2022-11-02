#ifndef LIGHT_H
#define LIGHT_H

#include "vec3.h"
#include <string>

class Light {
public:
    Vec3 position, intensity;
    std::string type;
};

#endif