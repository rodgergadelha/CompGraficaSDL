#ifndef OBSERVER_H
#define OBSERVER_H

#include "world.h"
#include "screen.h"
#include "sphere.h"
#include "matrix.h"
#include <vector>
#include <tuple>

class Observer {
public:
    std::tuple<Object*, Vec3> lookToWindow(Vec3 position, Vec3 d, World world) {
        Object *closestObject = nullptr;
        double closestT = std::numeric_limits<double>::infinity();
        std::vector<Object*> objects = world.objects;
        int objectsSize = objects.size();

        for(int i = 0; i < objectsSize; i++) {
            Object *object = objects.at(i);
            double t = object->intersection(position, d);
            
            if(t > 0 && t < closestT) {
                closestT = t;
                closestObject = object;
            }
        }

        if(closestObject == nullptr) {
            Vec3 bgColor(100, 100, 100);
            return std::make_tuple(closestObject, bgColor);;
        }

        Vec3 intersectionPoint = position + (d * closestT);
        Vec3 lighting = closestObject->computeLighting(intersectionPoint,
        d, world.lights, objects);
        Vec3 objectColor = closestObject->getColor(world.applyWt(intersectionPoint, false));

        return std::make_tuple(closestObject, objectColor % lighting);
    }

    void paintScreen(World world, Screen *screen) {
        double x, y;
        Window window = world.window;
        double dx = window.width/screen->width;
        double dy = window.heigth/screen->height;
        Vec3 position;

        for(int row = 0; row < screen->height; row++) {
            y = window.heigth/2 - dy/2 - dy * row;
            for(int column = 0; column < screen->width; column++) {
                x = -window.width/2 + dx/2 + dx * column;

                if(world.isOrtho) position = Vec3(x, y, 0);

                Vec3 view(x, y, -window.distanceFromObserver);
                Vec3 d = view - position;
                std::tuple<Object*, Vec3> objectAndColor = lookToWindow(position, d/d.getLength(), world);
                Object* object = get<0>(objectAndColor);
                Vec3 color = get<1>(objectAndColor);

                if(color.x > 255) color.x = 255;
                if(color.y > 255) color.y = 255;
                if(color.z > 255) color.z = 255;

                screen->pixel(object, color, column, row);
            }
        }
    }

    

};

#endif