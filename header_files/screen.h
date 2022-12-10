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
    const Uint8* state;
    int width, height;
    int mouseX, mouseY;
    bool update;

    Screen(int width, int height) {
        this->width = width;
        this->height = height;
        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
        SDL_RenderSetScale(renderer, 1, 1);
        canvas_objects.resize(height, std::vector<Object*>(width));
        this->state = SDL_GetKeyboardState(nullptr);
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

    void menuCamera(World* world) {
        std::cout << "---------------------- MUDAR PARÂMETROS DA CÂMERA ----------------------\n";
        std::cout << "1 - Mudar vetor eye\n";
        std::cout << "2 - Mudar vetor lookAt\n";
        std::cout << "3 - Mudar vetor viewUp\n";
        std::cout << "4 - Voltar ao menu principal";

        std::string resp;
        std::cin >> resp;
        
        std::string vetor;
        Vec3* vetorEscolhido;
        if(resp == "4") return;
        if(resp == "1") {vetor = "eye"; vetorEscolhido = &(world->eye);}
        if(resp == "2") {vetor = "lookAt"; vetorEscolhido = &(world->lookAt);}
        if(resp == "3") {vetor = "viewUp"; vetorEscolhido = &(world->viewUp);}

        double x, y, z;

        std::cout << vetor << ".x: ";
        std::cin >> x;
        
        std::cout << vetor << ".y: ";
        std::cin >> y;
        
        std::cout << vetor << ".z: ";
        std::cin >> z;

        if(resp == "1") world->eye.setCoordinates(x, y, z);
        if(resp == "2") world->lookAt.setCoordinates(x, y, z);
        if(resp == "3") world->viewUp.setCoordinates(x, y, z);
 
        this->update = true;
    }

    void menuLuzes(World* world) {
        std::cout << "---------------------- APAGAR OU ACENDER LUZES ----------------------\n";
        std::cout << "1 - Mudar parâmetros de câmera\n";
    }

    void menuProjecao(World* world) {
        std::cout << "---------------------- MUDAR PROJEÇÃO DA CENA ----------------------\n";
        std::cout << "1 - Mudar parâmetros de câmera\n";
    }

    void menu(World* world) {
        std::cout << "---------------------- MENU ----------------------\n";
        std::cout << "1 - Mudar parâmetros de câmera\n";
        std::cout << "2 - Apagar ou acender luzes\n";
        std::cout << "3 - Mudar projeção da cena\n";
        std::cout << "4 - Sair do menu\n";
        
        std::string resp;
        std::cin >> resp;

        if(resp == "1") menuCamera(world);
        else if(resp == "2") menuLuzes(world);
        else if(resp == "3") menuProjecao(world);
        else if(resp == "4") return;
    }

    bool input(World* world) {
        this->update = false;

        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                SDL_Quit();
                exit(0);
            }

            if(state[SDL_SCANCODE_BACKSPACE]) {
               menu(world);
            }

            if(e.type == SDL_MOUSEBUTTONDOWN) {
                SDL_GetMouseState(&mouseX, &mouseY);
                Object* o = picking(mouseX, mouseY);
                
                if(o == nullptr) {std::cout << "Nenhum objeto selecionado."; return false;}
                
                std::cout << o->type << "\n";

                // double x, y, z;
                // std::cout << "R: ";
                // std::cin >> x;
                // std::cout << "G: ";
                // std::cin >> y;
                // std::cout << "B: ";
                // std::cin >> z;
                // o->color.setCoordinates(x, y, z);
            }

            
        }

        return this->update;
    }

};

#endif