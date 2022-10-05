#include "header_files/observer.h"
#include "header_files/world.h"
#include "header_files/plane.h"

int main(int argv, char** args) {
    Screen screen(500, 500);
    
    World world;

    Window window;
    window.width = 60;
    window.heigth = 60;
    window.distanceFromObserver = 30;
    window.center.setCoordinates(0, 0, -window.distanceFromObserver);

    Light pontualLight;
    pontualLight.type = "pontual";
    pontualLight.position.setCoordinates(0, 60, -window.distanceFromObserver);
    pontualLight.intensity.setCoordinates(0.7, 0.7, 0.7);

    Light ambientLight;
    ambientLight.type = "ambient";
    ambientLight.intensity.setCoordinates(0.3, 0.3, 0.3);

    Sphere sphere;
    sphere.type = "sphere";
    sphere.radius = 40;
    sphere.center.setCoordinates(0, 0, -100);
    sphere.color.setCoordinates(255, 0, 0);
    sphere.kd.setCoordinates(0.7, 0.7, 0.2);
    sphere.ke.setCoordinates(0.7, 0.7, 0.2);
    sphere.ka.setCoordinates(0.7, 0.7, 0.2);
    sphere.shininess = 10;

    Plane plane;
    plane.type = "plane";
    plane.pPi.setCoordinates(0, -sphere.radius, 0);
    plane.normal.setCoordinates(0, 1, 0);
    plane.color.setCoordinates(0, 255, 0);
    plane.kd.setCoordinates(0.2, 0.7, 0.2);
    plane.ke.setCoordinates(0, 0, 0);
    plane.ka.setCoordinates(0.2, 0.7, 0.2);
    plane.shininess = 1;

    Plane plane2;
    plane2.type = "plane";
    plane2.pPi.setCoordinates(0, 0, -200);
    plane2.normal.setCoordinates(0, 0, 1);
    plane2.color.setCoordinates(0, 0, 255);
    plane2.kd.setCoordinates(0.3, 0.3, 0.7);
    plane2.ke.setCoordinates(0, 0, 0);
    plane2.ka.setCoordinates(0.3, 0.3, 0.7);
    plane2.shininess = 1;

    world.window = window;
    world.objects.push_back(&sphere);
    world.objects.push_back(&plane);
    world.objects.push_back(&plane2);
    world.lights.push_back(pontualLight);
    world.lights.push_back(ambientLight);

    Observer observer;
    observer.position.setCoordinates(0, 0, 0);
    observer.paintScreen(world, &screen);

    while(true) {
        screen.show();
        screen.input();
    }

    return 0;
}