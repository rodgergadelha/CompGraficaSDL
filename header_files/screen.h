#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>
#include <vector>
#include "vec3.h"
#include "world.h"
#include "object.h"
#include "spot_light.h"
#include "point_light.h"
#include "directional_light.h"
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
        std::cout << "---------------------- MUDAR PARAMETROS DA CAMERA ----------------------\n";
        std::cout << "1 - Mudar vetor eye\n";
        std::cout << "2 - Mudar vetor lookAt\n";
        std::cout << "3 - Mudar vetor viewUp\n";
        std::cout << "4 - Voltar ao menu principal\n";

        std::string resp;
        std::cin >> resp;
        
        std::string vetor;
        if(resp == "4") return;
        if(resp == "1") vetor = "eye";
        if(resp == "2") vetor = "lookAt";
        if(resp == "3") vetor = "viewUp";

        double x, y, z;

        std::cout << vetor << ".x: ";
        std::cin >> x;
        
        std::cout << vetor << ".y: ";
        std::cin >> y;
        
        std::cout << vetor << ".z: ";
        std::cin >> z;

        Vec3 eyeCopy(world->eye.x, world->eye.y, world->eye.z);
        Vec3 lookAtCopy(world->lookAt.x, world->lookAt.y, world->lookAt.z);
        Vec3 viewUpCopy(world->viewUp.x, world->viewUp.y, world->viewUp.z);

        if(resp == "1") {
            eyeCopy.setCoordinates(x, y, z);
            viewUpCopy.setCoordinates(x, y + 10, z);
        }

        if(resp == "2") {
            lookAtCopy = Vec3(x, y, z);
        }

        if(resp == "3") {
            viewUpCopy = Vec3(x, y, z);
        }

        world->applyCameraToWorld();
        world->applyWorldToCamera(eyeCopy, lookAtCopy, viewUpCopy);
 
        this->update = true;
    }

    void menuLuzes(World* world) {
        std::cout << "---------------------- MODIFICAR LUZES ----------------------\n";
        std::cout << "1 - Point light\n";
        std::cout << "2 - Spot light\n";
        std::cout << "3 - Directional light\n";
        std::cout << "4 - Voltar ao menu principal\n";
        
        std::string resp;
        std::cin >> resp;

        if(resp == "1") {
            PointLight* pl = static_cast<PointLight*>(world->lights[0]);
            std::cout << "1 - Modificar intensidade\n";
            std::cout << "2 - Modificar posicao\n"; 
            std::cin >> resp;
            double x, y, z;

            if(resp == "1") {
                std::cout << "intensity.x: "; 
                std::cin >> x;
                std::cout << "intensity.y: "; 
                std::cin >> y;
                std::cout << "intensity.z: "; 
                std::cin >> z;

                pl->intensity.setCoordinates(x, y, z);
            }

            if(resp == "2") {
                std::cout << "position.x: "; 
                std::cin >> x;
                std::cout << "position.y: "; 
                std::cin >> y;
                std::cout << "position.z: "; 
                std::cin >> z;

                pl->position.setCoordinates(x, y, z);
            }

        }
        else if(resp == "2") {
            SpotLight* sl = static_cast<SpotLight*>(world->lights[1]);
            std::cout << "1 - Modificar intensidade\n";
            std::cout << "2 - Modificar direcao\n";
            std::cout << "3 - Modificar angulo de abertura\n"; 
            std::cin >> resp;
            double x, y, z;

            if(resp == "1") {
                std::cout << "intensity.x: "; 
                std::cin >> x;
                std::cout << "intensity.y: "; 
                std::cin >> y;
                std::cout << "intensity.z: "; 
                std::cin >> z;

                sl->intensity.setCoordinates(x, y, z);
            }

            if(resp == "2") {
                std::cout << "position.x: "; 
                std::cin >> x;
                std::cout << "position.y: "; 
                std::cin >> y;
                std::cout << "position.z: "; 
                std::cin >> z;

                Vec3 position(x, y, z);

                std::cout << "spotPoint.x: "; 
                std::cin >> x;
                std::cout << "spotPoint.y: "; 
                std::cin >> y;
                std::cout << "spotPoint.z: "; 
                std::cin >> z;

                Vec3 spotPoint(x, y, z);
                Vec3 spotDirection = spotPoint - position;
                sl->spotDirection.setCoordinates(spotDirection.x, spotDirection.y, spotDirection.z);
            }

            if(resp == "3") {
                double cutoff;
                std::cout << "Angulo de aberura(em graus): "; 
                std::cin >> cutoff;
                sl->cutoff = cutoff;
            }
        }
        else if(resp == "3") {
            DirectionalLight* dl = static_cast<DirectionalLight*>(world->lights[2]);
            std::cout << "1 - Modificar intensidade\n";
            std::cout << "2 - Modificar direcao\n";
            std::cin >> resp;
            double x, y, z;

            if(resp == "1") {
                std::cout << "intensity.x: "; 
                std::cin >> x;
                std::cout << "intensity.y: "; 
                std::cin >> y;
                std::cout << "intensity.z: "; 
                std::cin >> z;

                dl->intensity.setCoordinates(x, y, z);
            }

            if(resp == "2") {
                std::cout << "direction.x: "; 
                std::cin >> x;
                std::cout << "direction.y: "; 
                std::cin >> y;
                std::cout << "direction.z: "; 
                std::cin >> z;

                Vec3 direction(x, y, z);
                direction = direction / direction.getLength();
                dl->direction.setCoordinates(direction.x, direction.y, direction.z);
            }
        }
        else if(resp == "4") return;

        this->update = true;
    }

    void menu(World* world) {
        std::cout << "---------------------- MENU ----------------------\n";
        std::cout << "1 - Mudar parametros de camera\n";
        std::cout << "2 - Modificar luzes\n";
        std::cout << "3 - Mudar projecao da cena\n";
        std::cout << "4 - Mudar distancia focal\n";
        std::cout << "5 - Mudar dimensoes da janela\n";
        std::cout << "6 - Sair do menu\n";
        
        std::string resp;
        std::cin >> resp;

        if(resp == "1") menuCamera(world);
        else if(resp == "2") menuLuzes(world);
        else if(resp == "3") {
            world->isOrtho = !(world->isOrtho);
            this->update = true;
        }
        else if(resp == "4") {
            std::cout << "distancia focal: ";
            int distanciaFocal;
            std::cin >> distanciaFocal;
            world->window.distanceFromObserver = distanciaFocal;
            this->update = true;
        }
        else if(resp == "5") {
            int w, h;
            std::cout << "Comprimento: ";
            std::cin >> w;

            std::cout << "Altura: ";
            std::cin >> h;

            world->window.width = w;
            world->window.heigth = h;
            this->update = true;
        }
        else if(resp == "6") return;

        return menu(world);
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
                
                std::cout << "Objeto selecionado: " << o->type << "\n";
                std::cout << "1 - Mudar ka\n";
                std::cout << "2 - Mudar ke\n";
                std::cout << "3 - Mudar kd\n";
                
                std::string resp;
                std::cin >> resp;
                double x, y, z;
                this->update = true;

                if(resp == "1") {
                    std::cout << "ka.x: "; 
                    std::cin >> x;
                    std::cout << "ka.y: "; 
                    std::cin >> y;
                    std::cout << "ka.z: "; 
                    std::cin >> z;

                    o->ka.setCoordinates(x, y, z);
                }
                else if(resp == "2") {
                    std::cout << "ke.x: "; 
                    std::cin >> x;
                    std::cout << "ke.y: "; 
                    std::cin >> y;
                    std::cout << "ke.z: "; 
                    std::cin >> z;

                    o->ke.setCoordinates(x, y, z);
                }
                else if(resp == "3") {
                    std::cout << "kd.x: "; 
                    std::cin >> x;
                    std::cout << "kd.y: "; 
                    std::cin >> y;
                    std::cout << "kd.z: "; 
                    std::cin >> z;

                    o->kd.setCoordinates(x, y, z);
                }else{
                    
                this->update = false;
                }

            }

            
        }

        return this->update;
    }

};

#endif