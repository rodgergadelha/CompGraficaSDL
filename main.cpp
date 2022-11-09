#include "header_files/observer.h"
#include "header_files/world.h"
#include "header_files/plane.h"
#include "header_files/cilinder.h"
#include "header_files/cone.h"
#include "header_files/cube.h"

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
    pontualLight.position.setCoordinates(0, 80, -30);
    pontualLight.intensity.setCoordinates(0.7, 0.7, 0.7);

    Light ambientLight;
    ambientLight.type = "ambient";
    ambientLight.intensity.setCoordinates(0.3, 0.3, 0.3);

    Sphere sphere;
    sphere.type = "sphere";
    sphere.radius = 25;
    sphere.center.setCoordinates(0, -20, -70);
    sphere.color.setCoordinates(255, 255, 255);
    sphere.kd.setCoordinates(0.9, 0.9, 0.9);
    sphere.ke.setCoordinates(0.4, 0.4, 0.4);
    sphere.ka.setCoordinates(0.9, 0.9, 0.9);
    sphere.shininess = 10;
    std::cout << sphere.center.x << " " << sphere.center.y << " " << sphere.center.z << "\n";

    Sphere sphere2;
    sphere2.type = "sphere";
    sphere2.radius = 15;
    sphere2.center.setCoordinates(0, sphere.center.y + sphere.radius + sphere2.radius - 2, sphere.center.z);
    sphere2.color = sphere.color;
    sphere2.kd = sphere.kd;
    sphere2.ke = sphere.ke;
    sphere2.ka = sphere.ka;
    sphere2.shininess = 10;

    Cilinder cilinder;
    cilinder.type = "cilinder";
    cilinder.baseCenter.setCoordinates(0, -50, -100);
    cilinder.height = 60;
    cilinder.baseRadius = 3;
    Vec3 axis(0,1,0);
    cilinder.u = axis/axis.getLength();
    cilinder.color.setCoordinates(255, 0, 0);
    cilinder.kd.setCoordinates(0.5, 0.5, 0.8);
    cilinder.ke.setCoordinates(0.5, 0.5, 0.8);
    cilinder.ka.setCoordinates(0.5, 0.5, 0.8);
    cilinder.shininess = 10;
    cilinder.basePlane.pPi = cilinder.baseCenter*1;
    cilinder.basePlane.normal = cilinder.u*(-1);
    cilinder.topPlane.pPi = cilinder.baseCenter + cilinder.u*cilinder.height;
    cilinder.topPlane.normal = cilinder.u*cilinder.height;

    Cone cone;
    cone.type = "cone";
    cone.baseCenter.setCoordinates(sphere2.center.x, sphere2.center.y - 2, sphere2.center.z + sphere2.radius);
    cone.baseRadius = 2.5;
    cone.height = 5;
    Vec3 coneAxis(0,0,1);
    cone.n.setCoordinates(0, 0, 1);
    cone.color.setCoordinates(250, 115, 57);
    cone.kd.setCoordinates(0.8, 0.8, 0.5);
    cone.ke.setCoordinates(0.8, 0.5, 0.5);
    cone.ka.setCoordinates(0.8, 0.5, 0.5);
    cone.shininess = 10;
    cone.basePlane.pPi.setCoordinates(cone.baseCenter.x, cone.baseCenter.y, cone.baseCenter.z);
    cone.basePlane.normal.setCoordinates(-cone.n.x, -cone.n.y, -cone.n.z);

    Cone hat;
    hat.type = "cone";
    hat.baseCenter.setCoordinates(sphere2.center.x, sphere2.center.y + sphere2.radius - 1, sphere2.center.z);
    hat.baseRadius = 6;
    hat.height = 12;
    hat.n.setCoordinates(0, 1, 0);
    hat.color.setCoordinates(255, 0, 0);
    hat.kd.setCoordinates(0.8, 0.8, 0.5);
    hat.ke.setCoordinates(0.8, 0.5, 0.5);
    hat.ka.setCoordinates(0.8, 0.5, 0.5);
    hat.shininess = 10;
    hat.basePlane.pPi.setCoordinates(hat.baseCenter.x, hat.baseCenter.y, hat.baseCenter.z);
    hat.basePlane.normal.setCoordinates(-hat.n.x, -hat.n.y, -hat.n.z);

    Sphere hatTop;
    hatTop.type = "sphere";
    hatTop.radius = 2;
    hatTop.center.setCoordinates(hat.baseCenter.x, hat.baseCenter.y + hat.height + hatTop.radius - 1, hat.baseCenter.z);
    hatTop.color.setCoordinates(255, 255, 0);
    hatTop.kd = sphere.kd;
    hatTop.ke = sphere.ke;
    hatTop.ka = sphere.ka;
    hatTop.shininess = 10;

    Sphere eye1;
    eye1.type = "sphere";
    eye1.radius = 1.5;
    eye1.center.setCoordinates(cone.baseCenter.x - cone.baseRadius - 2.5, cone.baseCenter.y + 3, cone.baseCenter.z - eye1.radius);
    eye1.color.setCoordinates(0, 0, 0);
    eye1.kd.setCoordinates(0.9, 0.9, 0.9);
    eye1.ke.setCoordinates(0.4, 0.4, 0.4);
    eye1.ka.setCoordinates(0.9, 0.9, 0.9);
    eye1.shininess = 10;

    Sphere eye2;
    eye2.type = "sphere";
    eye2.radius = eye1.radius;
    eye2.center.setCoordinates(cone.baseCenter.x + cone.baseRadius + 2.5, eye1.center.y, eye1.center.z);
    eye2.color = eye1.color;
    eye2.kd = eye1.kd;
    eye2.ke = eye1.ke;
    eye2.ka = eye1.ka;
    eye2.shininess = eye1.shininess;

    Plane plane;
    plane.type = "plane";
    plane.pPi.setCoordinates(0, sphere.center.y - sphere.radius, 0);
    plane.normal.setCoordinates(0, 1, 0);
    plane.color.setCoordinates(255, 255, 255);
    plane.kd.setCoordinates(0.9, 0.9, 0.9);
    plane.ke.setCoordinates(0, 0, 0);
    plane.ka.setCoordinates(0.9, 0.9, 0.9);
    plane.shininess = 1;

    Plane plane2;
    plane2.type = "plane";
    plane2.pPi.setCoordinates(0, 0, -200);
    plane2.normal.setCoordinates(0, 0, 1);
    plane2.color.setCoordinates(48, 162, 255);
    plane2.kd.setCoordinates(0.9, 0.9, 0.9);
    plane2.ke.setCoordinates(0, 0, 0);
    plane2.ka.setCoordinates(0.8, 0.8, 0.8);
    plane2.shininess = 1;

    Cube cube(40, *new Vec3(0, 40, -100));
    cube.color.setCoordinates(255, 0, 0);
    cube.kd.setCoordinates(0.9, 0.9, 0.9);
    cube.ke.setCoordinates(0.5, 0.5, 0.5);
    cube.ka.setCoordinates(0.8, 0.8, 0.8);
    cube.shininess = 10;

    world.window = window;
    // world.objects.push_back(&cone);
    // world.objects.push_back(&hat);
    // world.objects.push_back(&hatTop);
    // world.objects.push_back(&sphere);
    // world.objects.push_back(&sphere2);
    // world.objects.push_back(&eye1);
    // world.objects.push_back(&eye2);
    world.objects.push_back(&cube);
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
