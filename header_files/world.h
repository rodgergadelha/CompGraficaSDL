#ifndef WORLD_H
#define WORLD_H

#include "window.h"
#include "object.h"
#include "light.h"
#include <vector>

class World {
public:
    Window window;
    std::vector<Object*> objects;
    std::vector<Light> lights;
};

#endif