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
#include "header_files/christmas_tree.h"
#include "header_files/master_shield.h"
#include "header_files/book.h"
#include "header_files/incand_lamp.h"
#include "header_files/positioned_directional_light.h"
#include "header_files/window_frame.h"
#include "header_files/shelf.h"
#include "header_files/mage.h"
#include "header_files/snow_man.h"
#include "header_files/jar.h"



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

    Plane floor;
    floor.pPi.setCoordinates(0, 0, 0);
    floor.normal.setCoordinates(0, 1, 0);
    floor.worldNormal.setCoordinates(0, 1, 0);
    floor.color.setCoordinates(255, 255, 255);
    floor.kd.setCoordinates(0.9, 0.9, 0.9);
    floor.ke.setCoordinates(0.3, 0.3, 0.3);
    floor.ka.setCoordinates(0.8, 0.8, 0.8);
    floor.shininess = 2;
    floor.loadImage("textures/wood2.jpg");

    Plane roof;
    roof.pPi.setCoordinates(0, 250, 0);
    roof.normal.setCoordinates(0, -1, 0);
    roof.worldNormal.setCoordinates(0, -1, 0);
    roof.color.setCoordinates(255, 250, 250);
    roof.kd.setCoordinates(0.9, 0.9, 0.9);
    roof.ke.setCoordinates(0, 0, 0);
    roof.ka.setCoordinates(0.9, 0.9, 0.9);
    roof.shininess = 1;

    Plane back_wall;
    back_wall.pPi.setCoordinates(0, 0, -300);
    back_wall.normal.setCoordinates(0, 0, 1);
    back_wall.worldNormal.setCoordinates(0, 0, 1);
    back_wall.color.setCoordinates(255, 250, 250);
    back_wall.kd.setCoordinates(0.9, 0.9, 0.9);
    back_wall.ke.setCoordinates(0.1, 0.1, 0.1);
    back_wall.ka.setCoordinates(0.8, 0.8, 0.8);
    back_wall.shininess = 1;

    Plane front_wall;
    front_wall.pPi.setCoordinates(0, 0, 300);
    front_wall.normal.setCoordinates(0, 0, -1);
    front_wall.worldNormal.setCoordinates(0, 0, -1);
    front_wall.color.setCoordinates(255, 250, 250);
    front_wall.kd.setCoordinates(0.9, 0.9, 0.9);
    front_wall.ke.setCoordinates(0.1, 0.1, 0.1);
    front_wall.ka.setCoordinates(0.8, 0.8, 0.8);
    front_wall.shininess = 1;

    Plane right_wall;
    right_wall.pPi.setCoordinates(300, 0, 0);
    right_wall.normal.setCoordinates(-1, 0, 0);
    right_wall.worldNormal.setCoordinates(-1, 0, 0);
    right_wall.color.setCoordinates(255, 250, 250);
    right_wall.kd.setCoordinates(0.9, 0.9, 0.9);
    right_wall.ke.setCoordinates(0.1, 0.1, 0.1);
    right_wall.ka.setCoordinates(0.8, 0.8, 0.8);
    right_wall.shininess = 1;

    Plane left_wall;
    left_wall.pPi.setCoordinates(-300, 0, 0);
    left_wall.normal.setCoordinates(1, 0, 0);
    left_wall.worldNormal.setCoordinates(1, 0, 0);
    left_wall.color.setCoordinates(255, 250, 250);
    left_wall.kd.setCoordinates(0.9, 0.9, 0.9);
    left_wall.ke.setCoordinates(0.1, 0.1, 0.1);
    left_wall.ka.setCoordinates(0.8, 0.8, 0.8);
    left_wall.shininess = 1;

    Icosahedron ico(5, Vec3(0, 75, -50));
    ico.color.setCoordinates(255, 0, 0);
    ico.kd.setCoordinates(0.7, 0.7, 0.7);
    ico.ke.setCoordinates(0.6, 0.6, 0.6);
    ico.ka.setCoordinates(0.7, 0.7, 0.7);
    ico.shininess = 20;

    Table table(Vec3(0, 70, -70), 180, 100, 3, 3, 70, 4);
    table.kd.setCoordinates(0.9, 0.9, 0.9);
    table.ke.setCoordinates(0.5, 0.5, 0.5);
    table.ka.setCoordinates(0.8, 0.8, 0.8);
    table.setShininess(10);

    Chair chair(Vec3(0, 45, -120), Vec3(0, 0, 0), 45, 45, 45, 45, 2.25, 45, 2.25, 18);

    Chair chair2(Vec3(90, 45, -115), Vec3(0, 0, 0), 45, 45, 45, 45, 2.25, 45, 2.25, 18);
    chair2.rotateY(90);

    Chair chair3(Vec3(-90, 45, -115), Vec3(0, 0, 0), 45, 45, 45, 45, 2.25, 45, 2.25, 18);
    chair3.rotateY(270);

    Shelf shelf(Vec3(-90, 90, -283), 110, 180, 34);
    shelf.kd.setCoordinates(0.4, 0.4, 0.4);
    shelf.ke.setCoordinates(0.1, 0.1, 0.1);
    shelf.ka.setCoordinates(0.4, 0.4, 0.4);
    shelf.setShininess(10);

    Frame frame(Vec3(90, 150, -300), Vec3(0, 1, -1), &world, 97, 120, 1);

    ChristmasTree ct(Vec3(220, 0,-220), 4, 50, 70, 150, 8);

    Lamp lamp(Vec3(0, 0, 0), &world, 25, 8, 6);
    lamp.translate(70, 72, -100);

    IncandLamp incandLamp(Vec3(0, 250, 0), &world, 2, 4, 3.5);

    MasterShield ms(Vec3(0, 85, -70), 20, 27);

    Book book(Vec3(0, 0, 0), 21, 1.5, 29);
    book.rotateY(90);
    book.translate(70, 72.25, -70);

    Mage mage(Vec3(16, 80.5, -50), 3, 2, 4, 6, 3);

    Snowman sm(Vec3(-16, 75.5, -50), 2, 4, 0.4, 0.7, 1.5, 1.5);

    Jar jar(Vec3(-200, 0, -264), 30, 30, 25, 80);

    world.window = window;
    world.objects.push_back(&ico);
    world.objects.push_back(&table);
    world.objects.push_back(&chair);
    world.objects.push_back(&chair2);
    world.objects.push_back(&chair3);
    world.objects.push_back(&ct);
    world.objects.push_back(&mage);
    world.objects.push_back(&sm);
    world.objects.push_back(&shelf);
    world.objects.push_back(&jar);
    world.objects.push_back(&frame);
    world.objects.push_back(&ms);
    world.objects.push_back(&book);
    world.objects.push_back(&floor);
    world.objects.push_back(&right_wall);
    world.objects.push_back(&left_wall);
    world.objects.push_back(&back_wall);
    world.objects.push_back(&front_wall);
    world.objects.push_back(&lamp);
    world.objects.push_back(&incandLamp);
    world.lights.push_back(&al);

    world.isOrtho = false;

    Observer observer;
    Vec3 eye(0, 150, 100);
    world.applyWorldToCamera(eye, Vec3(0, 70, -70), Vec3(eye.x, eye.y + 10, eye.z));
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
