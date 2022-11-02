#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>
#include <vector>
#include "vec3.h"
#include <iostream>

class Screen {
public:
    SDL_Event e;
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<SDL_FPoint> points;
    std::vector<Vec3> colors;
    int width, height;

    Screen(int width, int height) {
        this->width = width;
        this->height = height;
        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
        SDL_RenderSetScale(renderer, 1, 1);
    }

    void pixel(Vec3 color, float x, float y) {
        points.emplace_back(x, y);
        colors.push_back(color);
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

    void input() {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                SDL_Quit();
                exit(0);
            }
        }
    }

};

#endif