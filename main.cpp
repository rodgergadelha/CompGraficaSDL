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
#include "header_files/table.h"
#include "header_files/chair.h"
#include "header_files/lamp.h"
#include "header_files/closet.h"
#include "header_files/christmas_tree.h"
#include "header_files/master_shield.h"
#include "header_files/bed.h"
#include "header_files/book.h"
#include "header_files/incand_lamp.h"
#include "header_files/positioned_directional_light.h"
#include "header_files/window_frame.h"
#include "header_files/mage.h"
#include "header_files/snow_man.h"



int main(int argv, char** args) {
    std::srand((unsigned) time(NULL));

    Screen screen(600, 600);
    
    World world;

    Window window;
    window.width = 60;
    window.heigth = 60;
    window.distanceFromObserver = 30;
    window.center.setCoordinates(0, 0, -window.distanceFromObserver);

    PointLight pl;
    pl.position.setCoordinates(0, 80, -30);
    pl.intensity.setCoordinates(0.7, 0.7, 0.7);

    AmbientLight al;
    al.intensity.setCoordinates(0.3, 0.3, 0.3);

    DirectionalLight dl(Vec3(0, 1, 0));
    dl.intensity.setCoordinates(0.7, 0.7, 0.7);

    DirectionalLight dl2(Vec3(-1, 0, 0));
    dl2.intensity.setCoordinates(0.7, 0.7, 0.7);

    SpotLight sl(Vec3(0, 30, 0), Vec3(0, 0, -50), 5, 30);
    sl.intensity.setCoordinates(0.7, 0.7, 0.7);

    SpotLight sl2(Vec3(0, 40, 0), Vec3(0, 60, -50), 5, 30);
    sl2.intensity.setCoordinates(0.7, 0.7, 0.7);

    Sphere sphere;
    sphere.radius = 10;
    sphere.center.setCoordinates(0, 20, -50);
    sphere.color.setCoordinates(255, 0, 0);
    sphere.kd.setCoordinates(0.9, 0.9, 0.9);
    sphere.ke.setCoordinates(0.4, 0.4, 0.4);
    sphere.ka.setCoordinates(0.9, 0.9, 0.9);
    sphere.shininess = 10;

    Cilinder cilinder;
    cilinder.center.setCoordinates(0, 0, -50);
    cilinder.height = 20;
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
    cilinder.topPlane.normal = (cilinder.topPlane.pPi - cilinder.center) / (cilinder.topPlane.pPi - cilinder.center).getLength();
    cilinder.loadImage("textures/mini_cpp.png");

    Cone cone;
    cone.center.setCoordinates(0, 0, -50);
    cone.baseRadius = 5;
    cone.height = 15;
    cone.n.setCoordinates(0, 1, 0);
    cone.color.setCoordinates(250, 115, 57);
    cone.kd.setCoordinates(0.8, 0.8, 0.5);
    cone.ke.setCoordinates(0.8, 0.5, 0.5);
    cone.ka.setCoordinates(0.8, 0.5, 0.5);
    cone.shininess = 10;
    cone.basePlane.pPi.setCoordinates(cone.center.x, cone.center.y, cone.center.z);
    cone.basePlane.normal.setCoordinates(-cone.n.x, -cone.n.y, -cone.n.z);

    Plane floor;
    floor.pPi.setCoordinates(0, 0, 0);
    floor.normal.setCoordinates(0, 1, 0);
    floor.worldNormal.setCoordinates(0, 1, 0);
    floor.color.setCoordinates(255, 255, 255);
    floor.kd.setCoordinates(0.9, 0.9, 0.9);
    floor.ke.setCoordinates(0, 0, 0);
    floor.ka.setCoordinates(0.9, 0.9, 0.9);
    floor.shininess = 1;

    Plane back_wall;
    back_wall.pPi.setCoordinates(0, 0, -200);
    back_wall.normal.setCoordinates(0, 0, 1);
    back_wall.worldNormal.setCoordinates(0, 0, 1);
    back_wall.color.setCoordinates(48, 162, 255);
    back_wall.kd.setCoordinates(0.9, 0.9, 0.9);
    back_wall.ke.setCoordinates(0, 0, 0);
    back_wall.ka.setCoordinates(0.8, 0.8, 0.8);
    back_wall.shininess = 1;
    back_wall.loadImage("textures/bear.jpeg");

    Plane right_wall;
    right_wall.pPi.setCoordinates(20, 0, 0);
    right_wall.normal.setCoordinates(-1, 0, 0);
    right_wall.worldNormal.setCoordinates(-1, 0, 0);
    right_wall.color.setCoordinates(48, 162, 255);
    right_wall.kd.setCoordinates(0.9, 0.9, 0.9);
    right_wall.ke.setCoordinates(0, 0, 0);
    right_wall.ka.setCoordinates(0.8, 0.8, 0.8);
    right_wall.shininess = 1;
    right_wall.loadImage("textures/cpp_image.png");

    Cube cube(5, Vec3(0, 0, -50));
    cube.color.setCoordinates(255, 0, 0);
    cube.kd.setCoordinates(0.9, 0.9, 0.9);
    cube.ke.setCoordinates(0.6, 0.6, 0.6);
    cube.ka.setCoordinates(0.8, 0.8, 0.8);
    cube.shininess = 10;

    Icosahedron ico(45, Vec3(40, 60, -100));
    ico.color.setCoordinates(255, 0, 0);
    ico.kd.setCoordinates(0.9, 0.9, 0.9);
    ico.ke.setCoordinates(0.6, 0.6, 0.6);
    ico.ka.setCoordinates(0.8, 0.8, 0.8);
    ico.shininess = 20;

    Table table(Vec3(0, 0, -50), 80, 50, 2.5, 1, 30, 1);

    Chair chair(Vec3(0, 0, -50), Vec3(255, 0, 0), 20, 20, 20, 20, 1, 20, 1, 8);
    (static_cast<MeshObject*>(chair.components[0]))->loadImageAllFaces("textures/minecraft.png");
    (static_cast<MeshObject*>(chair.components[1]))->loadImageAllFaces("textures/wood.jpg");

    Closet closet(Vec3(0, 0, -50), Vec3(255, 0, 0), 10, 40, 10, 1, 2);
    (static_cast<MeshObject*>(closet.components[0]))->loadImageAllFaces("textures/mini_cpp.png");

    ChristmasTree ct(Vec3(0, 0,-50), 0.8, 15, 8, 20, 0.75);

    //Lamp lamp(Vec3(0, 0, -50), &world, 20, 7, 3.5);

    MasterShield ms(Vec3(0, 0, -35), 5, 5);

    Bed bed(Vec3(0, 0, -50), 10, 5, 25, 0.5, 0.5);

    Book book(Vec3(0, 0, -50), 10, 1.5, 15);

    //IncandLamp icl(Vec3(0, 20, -50), &world, 10, 5, 5);


    // PositionedDirectionalLight pdl(&sphere, Vec3(-1, 1, 0));
    // pdl.intensity.setCoordinates(0.7, 0.7, 0.7);

    Mage mage(Vec3(0, 50, -50), 10, 4, 7, 12, 3);

    Snowman sm(Vec3(0, 0, -50), 5, 10, 0.7, 0.7, 2.5, 2.5);

    world.window = window;
    //world.objects.push_back(&cilinder);
    world.objects.push_back(&sm);
    //world.objects.push_back(&table);
    //world.objects.push_back(&floor);
    //world.objects.push_back(&book);
    //world.objects.push_back(&right_wall);
    //world.objects.push_back(&back_wall);
    //world.lights.push_back(&dl);
    //world.lights.push_back(&dl2);
    world.lights.push_back(&pl);
    world.lights.push_back(&al);

    world.isOrtho = false;

    Observer observer;
    Vec3 eye(0, 10, 0);
    world.applyWorldToCamera(eye, Vec3(0, 0, -50), Vec3(eye.x, eye.y + 10, eye.z));
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
