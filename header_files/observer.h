#ifndef OBSERVER_H
#define OBSERVER_H

#include "world.h"
#include "screen.h"
#include "sphere.h"
#include "matrix.h"
#include "light.h"
#include "complex_object.h"
#include "positioned_directional_light.h"
#include "incand_lamp.h"
#include <vector>
#include <tuple>

class Observer {
public:

    bool checkShadow(Object *intersectedObject, Vec3 position, Light* light, std::vector<Object*> objects) {
        double closestTShadow = std::numeric_limits<double>::infinity();
        Object* closestObjectShadow = nullptr;
        Vec3 pf_sub_pi = light->getL(position);
        Vec3 l = pf_sub_pi / pf_sub_pi.getLength();
        
        for(auto object : objects) {
            Object *oldIntersectedComponent = &(*(static_cast<ComplexObject*>(intersectedObject)->intersectedComponent));
            double t = object->intersection(position, l);
            static_cast<ComplexObject*>(intersectedObject)->intersectedComponent = &(*oldIntersectedComponent);

            if(object == intersectedObject || t <= 0.001 || object->type == "plane") continue;

            if(t < closestTShadow && (t < pf_sub_pi.getLength() || light->getType() == "directional" || light->getType() == "pos directional")) {
                closestTShadow = t;
                closestObjectShadow = object;
            }
        }

        if(light->getType() == "pos directional" && static_cast<PositionedDirectionalLight*>(light)->emiter == closestObjectShadow)
        {return false;}

        if( closestObjectShadow != nullptr && light->getType() == "point" && static_cast<IncandLamp*>(closestObjectShadow)->light == light)
        {return false;}

        return closestObjectShadow != nullptr;
    }

    Vec3 computeLighting(Object* object, Vec3 intersectionPoint, Vec3 d, World world, std::vector<Object*> objects) {
        Vec3 normal = object->getNormal(intersectionPoint, d);
        Vec3 totalLighting;

        for(auto light : world.lights) {
            if(checkShadow(object, intersectionPoint, light, objects)) continue;
            
            totalLighting = totalLighting + light->getIntensity(intersectionPoint, d, normal, object);
        }

        for(auto light : world.complex_objects_lights) {
            if(checkShadow(object, intersectionPoint, light, objects)) continue;
            
            totalLighting = totalLighting + light->getIntensity(intersectionPoint, d, normal, object);
        }
        
        return totalLighting;
    }

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
            return std::make_tuple(closestObject, bgColor);
        }

        Vec3 intersectionPoint = position + (d * closestT);
        Vec3 lighting = computeLighting(closestObject, intersectionPoint, d, world, objects);
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