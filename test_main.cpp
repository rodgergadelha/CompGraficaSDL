#include "header_files/observer.h"
#include "header_files/world.h"
#include "header_files/plane.h"
#include "header_files/cilinder.h"
#include "header_files/cone.h"
#include "header_files/cube.h"
#include "header_files/icosahedron.h"
#include "header_files/point_light.h"
#include "header_files/ambient_light.h"
#include "header_files/directional_light.h"
#include "header_files/spot_light.h"

int main(int argv, char** args) {
    std::srand((unsigned) time(NULL));

    Screen screen(600, 600);
    
    World world;

    Window window;
    window.width = 600;
    window.heigth = 600;
    window.distanceFromObserver = 30;
    window.center.setCoordinates(0, 0, -window.distanceFromObserver);

    PointLight pl;
    pl.position.setCoordinates(-100, 140, -20);
    pl.intensity.setCoordinates(0, 0, 0);

    SpotLight sl(Vec3(0, 150, -20), Vec3(0, -60, -200), 5, 30);
    sl.intensity.setCoordinates(0.7, 0.7, 0.7);

    DirectionalLight dl(Vec3(0, -1, 0));
    dl.intensity.setCoordinates(0, 0, 0);

    AmbientLight al;
    al.intensity.setCoordinates(0.3, 0.3, 0.3);

    Sphere sphere;
    sphere.radius = 5;
    sphere.center.setCoordinates(0, 95, -200);
    sphere.color.setCoordinates(255, 255, 255);
    sphere.kd.setCoordinates(0.854, 0.647, 0.125);
    sphere.ke.setCoordinates(0.854, 0.647, 0.125);
    sphere.ka.setCoordinates(0.854, 0.647, 0.125);
    sphere.shininess = 10;


    Cilinder cilinder;
    cilinder.center.setCoordinates(0, -150, -200);
    cilinder.height = 90;
    cilinder.baseRadius = 5;
    Vec3 axis(0,1,0);
    cilinder.u = axis/axis.getLength();
    cilinder.color.setCoordinates(255, 0, 0);
    cilinder.kd.setCoordinates(0.824, 0.706, 0.549);
    cilinder.ke.setCoordinates(0.824, 0.706, 0.549);
    cilinder.ka.setCoordinates(0.824, 0.706, 0.549);
    cilinder.shininess = 10;
    cilinder.basePlane.pPi = cilinder.center*1;
    cilinder.basePlane.normal = cilinder.u*(-1);
    cilinder.topPlane.pPi = cilinder.center + cilinder.u*cilinder.height;
    cilinder.topPlane.normal = cilinder.u*cilinder.height;

    Cone cone;
    cone.center.setCoordinates(0, -60, -200);
    cone.baseRadius = 90;
    cone.height = 150;
    cone.n.setCoordinates(0, 1, 0);
    cone.color.setCoordinates(250, 115, 57);
    cone.kd.setCoordinates(0., 1., 0.498);
    cone.ke.setCoordinates(0., 1., 0.498);
    cone.ka.setCoordinates(0., 1., 0.498);
    cone.shininess = 10;
    cone.basePlane.pPi.setCoordinates(cone.center.x, cone.center.y, cone.center.z);
    cone.basePlane.normal.setCoordinates(-cone.n.x, -cone.n.y, -cone.n.z);

    Plane floor;
    floor.pPi.setCoordinates(0, -150, 0);
    floor.normal.setCoordinates(0, 1, 0);
    floor.worldNormal.setCoordinates(0, 1, 0);
    floor.kd.setCoordinates(0.9, 0.9, 0.9);
    floor.ke.setCoordinates(0, 0, 0);
    floor.ka.setCoordinates(0.9, 0.9, 0.9);
    floor.shininess = 1;
    floor.loadImage("textures/wood.jpg");

    Plane back_wall;
    back_wall.pPi.setCoordinates(200, -150, -400);
    back_wall.normal.setCoordinates(0, 0, 1);
    back_wall.worldNormal.setCoordinates(0, 0, 1);
    back_wall.color.setCoordinates(48, 162, 255);
    back_wall.kd.setCoordinates(0.686, 0.933, 0.933);
    back_wall.ke.setCoordinates(0.686, 0.933, 0.933);
    back_wall.ka.setCoordinates(0.686, 0.933, 0.933);
    back_wall.shininess = 1;
    back_wall.loadImage("textures/mountain.jpg");


    Plane right_wall;
    right_wall.pPi.setCoordinates(200, -150, 0);
    right_wall.normal.setCoordinates(-1, 0, 0);
    right_wall.worldNormal.setCoordinates(-1, 0, 0);
    right_wall.color.setCoordinates(48, 162, 255);
    right_wall.kd.setCoordinates(0.686, 0.933, 0.933);
    right_wall.ke.setCoordinates(0.686, 0.933, 0.933);
    right_wall.ka.setCoordinates(0.686, 0.933, 0.933);
    right_wall.shininess = 1;

    Plane left_wall;
    left_wall.pPi.setCoordinates(-200, -150, 0);
    left_wall.normal.setCoordinates(1, 0, 0);
    left_wall.worldNormal.setCoordinates(1, 0, 0);
    left_wall.color.setCoordinates(48, 162, 255);
    left_wall.kd.setCoordinates(0.686, 0.933, 0.933);
    left_wall.ke.setCoordinates(0.686, 0.933, 0.933);
    left_wall.ka.setCoordinates(0.686, 0.933, 0.933);
    left_wall.shininess = 1;

    Plane roof;
    roof.pPi.setCoordinates(0, 150, 0);
    roof.normal.setCoordinates(0, -1, 0);
    roof.worldNormal.setCoordinates(0, -1, 0);
    roof.color.setCoordinates(48, 162, 255);
    roof.kd.setCoordinates(0.933, 0.933, 0.933);
    roof.ke.setCoordinates(0.933, 0.933, 0.933);
    roof.ka.setCoordinates(0.933, 0.933, 0.933);
    roof.shininess = 1;

    Cube cube(40, Vec3(0, 0, 0));
    cube.color.setCoordinates(255, 0, 0);
    cube.kd.setCoordinates(1., 0.078, 0.576);
    cube.ke.setCoordinates(1., 0.078, 0.576);
    cube.ka.setCoordinates(1., 0.078, 0.576);
    cube.shininess = 10;
    cube.translate(0, 0, -165);

    world.window = window;
    world.objects.push_back(&cone);
    world.objects.push_back(&cilinder);
    //world.objects.push_back(&cube);
    world.objects.push_back(&floor);
    world.objects.push_back(&right_wall);
    world.objects.push_back(&left_wall);
    //world.objects.push_back(&back_wall);
    //world.objects.push_back(&roof);
    world.lights.push_back(&pl);
    world.lights.push_back(&sl);
    world.lights.push_back(&dl);
    world.lights.push_back(&al);

    world.isOrtho = true;

    Observer observer;
    Vec3 eye(10, 10, 0);
    world.applyWorldToCamera(eye, Vec3(0, 0, -200), Vec3(eye.x, eye.y + 10, eye.z));
    observer.paintScreen(world, &screen);
    

    while(true) {
        screen.show();
        
        if(screen.input(&world)) {
            screen.clear();
            screen.updateWindow();
            observer.paintScreen(world, &screen);
        }
    }

    return 0;
}
