#include "header_files/observer.h"
#include "header_files/world.h"
#include "header_files/plane.h"
#include "header_files/cilinder.h"
#include "header_files/cone.h"

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

    Cilinder cilinder;
    cilinder.type = "cilinder";
    cilinder.baseCenter.setCoordinates(sphere.center.x, sphere.center.y, sphere.center.z);
    cilinder.height = 3 * sphere.radius;
    cilinder.baseRadius = sphere.radius/3;
    cilinder.u.setCoordinates(-1/sqrt(3), 1/sqrt(3), -1/sqrt(3));
    cilinder.color.setCoordinates(255, 0, 0);
    cilinder.kd.setCoordinates(0.2, 0.3, 0.8);
    cilinder.ke.setCoordinates(0.2, 0.3, 0.8);
    cilinder.ka.setCoordinates(0.2, 0.3, 0.8);
    cilinder.shininess = 10;
    cilinder.basePlane.pPi.setCoordinates(cilinder.baseCenter.x, cilinder.baseCenter.y, cilinder.baseCenter.z);
    cilinder.basePlane.normal.setCoordinates(-cilinder.u.x, -cilinder.u.y, -cilinder.u.z);
    cilinder.topPlane.pPi.setCoordinates(cilinder.baseCenter.x + cilinder.u.x*cilinder.height,
    cilinder.baseCenter.y  + cilinder.u.y*cilinder.height,
    cilinder.baseCenter.z + cilinder.u.z*cilinder.height);
    cilinder.topPlane.normal.setCoordinates(cilinder.u.x*cilinder.height,
    cilinder.u.y*cilinder.height,
    cilinder.u.z*cilinder.height);

    Cone cone;
    cone.type = "cone";
    cone.baseCenter.setCoordinates(cilinder.topPlane.pPi.x,
    cilinder.topPlane.pPi.y, cilinder.topPlane.pPi.z);
    cone.baseRadius = 3*sphere.radius;
    cone.height = cone.baseRadius/3;
    cone.n.setCoordinates(-1/sqrt(3), 1/sqrt(3), -1/sqrt(3));
    cone.color.setCoordinates(255, 0, 0);
    cone.kd.setCoordinates(0.8, 0.3, 0.2);
    cone.ke.setCoordinates(0.8, 0.3, 0.2);
    cone.ka.setCoordinates(0.8, 0.3, 0.2);
    cone.shininess = 10;
    cone.theta = 0.52;
    cone.basePlane.pPi.setCoordinates(cone.baseCenter.x, cone.baseCenter.y, cone.baseCenter.z);
    Vec3 basePlaneNormal = ((cone.baseCenter - cone.getVertex()) + cone.n); 
    cone.basePlane.normal.setCoordinates(cone.n.x, cone.n.y, cone.n.z);

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
    plane2.color.setCoordinates(100, 100, 100);
    plane2.kd.setCoordinates(0.3, 0.3, 0.7);
    plane2.ke.setCoordinates(0, 0, 0);
    plane2.ka.setCoordinates(0.3, 0.3, 0.7);
    plane2.shininess = 1;

    world.window = window;
    world.objects.push_back(&cone);
    //world.objects.push_back(&cilinder);
    //world.objects.push_back(&sphere);
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