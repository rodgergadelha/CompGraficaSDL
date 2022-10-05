#include "world.h"
#include "screen.h"
#include "sphere.h"
#include <vector>

#ifndef OBSERVER_H
#define OBSERVER_H

class Observer {
public:
    Vec3 position;

    Vec3 lookToWindow(Vec3 position, Vec3 view, World world) {
        Object *closestObject = nullptr;
        double closestT = std::numeric_limits<double>::infinity();
        std::vector<Object*> objects = world.objects;
        int objectsSize = objects.size();

        for(int i = 0; i < objectsSize; i++) {
            Object *object = objects.at(i);
            std::vector<double> t = object->intersection(position, view);
            
            if(t.size() == 0) continue;
            
            if(object->type == "sphere") {
                double t1 = t.at(0);
                double t2 = t.at(1);

                if(t1 > 0 && t1 < closestT) {
                    closestT = t1;
                    closestObject = object;
                }

                if(t2 > 0 && t2 < closestT) {
                    closestT = t2;
                    closestObject = object;
                }
            }

            if(object->type == "plane") {
                double ti = t.at(0);

                if(ti < closestT) {
                    closestT = ti;
                    closestObject = object;
                }
            }
            
        }


        if(closestObject == nullptr) {
            Vec3 bgColor(100, 100, 100);
            return bgColor;
        }

        Vec3 intersectionPoint = position + (view * closestT);
        Vec3 direction = view - position;
        Vec3 lighting = closestObject->computeLighting(intersectionPoint,
        direction, world.lights, objects);
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
                Vec3 color = lookToWindow(position, view, world);

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