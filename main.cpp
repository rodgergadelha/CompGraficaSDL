#include "header_files/observer.h"
#include "header_files/world.h"
#include "header_files/plane.h"
#include "header_files/cilinder.h"
#include "header_files/cone.h"
#include "header_files/cube.h"
#include "header_files/point_light.h"
#include "header_files/ambient_light.h"
#include "header_files/directional_light.h"
#include "header_files/spot_light.h"

int main(int argv, char** args) {
    Screen screen(500, 500);
    
    World world;

    Window window;
    window.width = 60;
    window.heigth = 60;
    window.distanceFromObserver = 30;
    window.center.setCoordinates(0, 0, -window.distanceFromObserver, 0);

    PointLight pl;
    pl.position.setCoordinates(0, 80, -30);
    pl.intensity.setCoordinates(0.7, 0.7, 0.7);

    AmbientLight al;
    al.intensity.setCoordinates(0.3, 0.3, 0.3);

    DirectionalLight dl(Vec3(0, 1, 0));
    dl.intensity.setCoordinates(0.7, 0.7, 0.7);

    SpotLight sl(Vec3(0, 40, 0), Vec3(0, 0, -50), 5, 0.5235987756);
    sl.intensity.setCoordinates(0.7, 0.7, 0.7);

    Sphere sphere;
    sphere.type = "sphere";
    sphere.radius = 25;
    sphere.center.setCoordinates(0, -20, -70);
    sphere.color.setCoordinates(255, 255, 255);
    sphere.kd.setCoordinates(0.9, 0.9, 0.9);
    sphere.ke.setCoordinates(0.4, 0.4, 0.4);
    sphere.ka.setCoordinates(0.9, 0.9, 0.9);
    sphere.shininess = 10;

    Cilinder cilinder;
    cilinder.type = "cilinder";
    cilinder.center.setCoordinates(0, -50, -100);
    cilinder.height = 60;
    cilinder.baseRadius = 3;
    Vec3 axis(0,1,0);
    cilinder.u = axis/axis.getLength();
    cilinder.color.setCoordinates(255, 0, 0);
    cilinder.kd.setCoordinates(0.5, 0.5, 0.8);
    cilinder.ke.setCoordinates(0.5, 0.5, 0.8);
    cilinder.ka.setCoordinates(0.5, 0.5, 0.8);
    cilinder.shininess = 10;
    cilinder.basePlane.pPi = cilinder.center*1;
    cilinder.basePlane.normal = cilinder.u*(-1);
    cilinder.topPlane.pPi = cilinder.center + cilinder.u*cilinder.height;
    cilinder.topPlane.normal = cilinder.u*cilinder.height;

    Cone cone;
    cone.type = "cone";
    cone.center.setCoordinates(sphere.center.x, sphere.center.y - 2, sphere.center.z + sphere.radius);
    cone.baseRadius = 2.5;
    cone.height = 5;
    Vec3 coneAxis(0,0,1);
    cone.n.setCoordinates(0, 0, 1);
    cone.color.setCoordinates(250, 115, 57);
    cone.kd.setCoordinates(0.8, 0.8, 0.5);
    cone.ke.setCoordinates(0.8, 0.5, 0.5);
    cone.ka.setCoordinates(0.8, 0.5, 0.5);
    cone.shininess = 10;
    cone.basePlane.pPi.setCoordinates(cone.center.x, cone.center.y, cone.center.z);
    cone.basePlane.normal.setCoordinates(-cone.n.x, -cone.n.y, -cone.n.z);

//     Plano 1: Chão
// >> Ponto P_pi = (0, -150cm, 0)
// >> Vetor unitário normal ao plano: n = (0, 1., 0.)
// >> Kd = Ke = Ka = Textura de madeira


    Plane plane;
    plane.type = "plane";
    plane.pPi.setCoordinates(0, -60, 0);
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

    Cube cube(30, Vec3(0, 0, 0));
    cube.color.setCoordinates(255, 0, 0);
    cube.kd.setCoordinates(0.9, 0.9, 0.9);
    cube.ke.setCoordinates(0.6, 0.6, 0.6);
    cube.ka.setCoordinates(0.8, 0.8, 0.8);
    cube.shininess = 15;
    cube.rotateX(30);
    cube.translate(0, 0, -50);

    world.window = window;
    //world.objects.push_back(&cone);
    // world.objects.push_back(&hat);
    // world.objects.push_back(&hatTop);
    //world.objects.push_back(&sphere);
    // world.objects.push_back(&sphere2);
    // world.objects.push_back(&eye1);
    // world.objects.push_back(&eye2);
    world.objects.push_back(&cube);
    world.objects.push_back(&plane);
    world.objects.push_back(&plane2);
    world.lights.push_back(&sl);
    world.lights.push_back(&al);

    Observer observer;
    observer.position.setCoordinates(0, 0, 0, 0);
    world.applyWorldToCamera(Vec3(0, 40, 0), Vec3(0, 0, -50), Vec3(0, 50, 0));
    observer.paintScreen(world, &screen);

    while(true) {
        screen.show();
        screen.input();
    }

    return 0;
}
