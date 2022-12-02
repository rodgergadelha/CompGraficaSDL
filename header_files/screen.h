#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>
#include <vector>
#include "vec3.h"
#include "world.h"
#include "object.h"
#include "light.h"
#include <iostream>

class Screen {
public:
    SDL_Event e;
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<SDL_FPoint> points;
    std::vector<Vec3> colors;
    std::vector<std::vector<Object*>> canvas_objects;
    int width, height;
    int mouseX, mouseY;

    Screen(int width, int height) {
        this->width = width;
        this->height = height;
        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
        SDL_RenderSetScale(renderer, 1, 1);
        canvas_objects.resize(height, std::vector<Object*>(width));
    }

    void pixel(Object* object, Vec3 color, float x, float y) {
        points.emplace_back(x, y);
        colors.push_back(color);
        canvas_objects[x][y] = object;
    }

    void show() {
        SDL_RenderClear(renderer);

        for(int i = 0; i < points.size(); i++) {
            SDL_FPoint point = points.at(i);
            Vec3 pointColor = colors.at(i);
            
            SDL_SetRenderDrawColor(renderer, pointColor.x, pointColor.y, pointColor.z, 255);
            SDL_RenderDrawPointF(renderer, point.x, point.y);
        }

        SDL_RenderPresent(renderer);
    }

    void clear() {
        points.clear();
        colors.clear();
    }

    void updateWindow() {
        SDL_UpdateWindowSurface(window);
    }

    Object* picking(int row, int column) {
        return canvas_objects[row][column];
    }

    bool input(World* world, bool isOrtho) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                SDL_Quit();
                exit(0);
            }

            if(e.type == SDL_MOUSEBUTTONDOWN) {
                SDL_GetMouseState(&mouseX, &mouseY);
                Object* o = picking(mouseX, mouseY);
                
                if(o == nullptr) {std::cout << "Nenhum objeto selecionado."; return false;}
                
                std::cout << o->type << "\n";

                double x, y, z;
                std::cout << "R: ";
                std::cin >> x;
                std::cout << "G: ";
                std::cin >> y;
                std::cout << "B: ";
                std::cin >> z;

                o->color.setCoordinates(x, y, z);

                // double x, y, z;
                // std::cout << "eye.x: ";
                // std::cin >> x;
                // std::cout << "eye.y: ";
                // std::cin >> y;
                // std::cout << "eye.z: ";
                // std::cin >> z;

                // Vec3 eye(x, y, z);
                // world->applyCameraToWorld();
                // world->applyWorldToCamera(eye, Vec3(0, 0, -50), Vec3(eye.x, eye.y + 10, eye.z));

                return true;

            }

            
        }

        return false;
    }

};

#endif