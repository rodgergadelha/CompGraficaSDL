#include "world.h"
#include "screen.h"
#include "sphere.h"
#include <vector>

#ifndef OBSERVER_H
#define OBSERVER_H

class Observer {
public:
    Vec3 position;

    Vec3 lookToWindow(Vec3 position, Vec3 d, World world) {
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
            return bgColor;
        }

        Vec3 intersectionPoint = position + (d * closestT);
        Vec3 lighting = closestObject->computeLighting(intersectionPoint,
        d, world.lights, objects);
        Vec3 objectColor = closestObject->color;

        return objectColor % lighting;
    }

    void paintScreen(World world, Screen *screen) {
        double x, y;
        Window window = world.window;
        double dx = window.width/screen->width;
        double dy = window.heigth/screen->height;

        for(int row = 0; row < screen->height; row++) {
            y = window.heigth/2 - dy/2 - dy * row;
            for(int column = 0; column < screen->width; column++) {
                x = -window.width/2 + dx/2 + dx * column;

                Vec3 view(x, y, -window.distanceFromObserver);
                Vec3 d = view - position;
                Vec3 color = lookToWindow(position, d/d.getLength(), world);

                if(color.x > 255) {
                    color.x = 255;
                }

                if(color.y > 255) {
                    color.y = 255;
                }

                if(color.z > 255) {
                    color.z = 255;
                }

                screen->pixel(color, column, row);

            }
        }
    }

};

#endif