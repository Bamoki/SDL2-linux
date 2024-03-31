#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string.h>

#include "engine.cpp"
#include "player.hpp"
#include "enemy.hpp"

//variables
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
const std::string h = "test 0.0.1";
SDL_Rect text;

bool run = true;

int main(int argc, char* args[]){

    //iniciar sdl2, si inicia bien que se cree la ventana
    if(SDL_Init(SDL_INIT_EVERYTHING) >= 0){
        window = SDL_CreateWindow("hola",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,740,540,SDL_WINDOW_SHOWN);
    }
    //comprobar que la ventana no este vacia
    if(window == nullptr){
        std::cerr<<"not load window\n";
    }
    //crear render
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //comprobar que render no este vacio
    if (renderer == nullptr){
        std::cerr<<"not load renderer";
    }
    //iniciar ttf
    if(TTF_Init() <  0){
        std::cout<<"not load sdl2_ttf"<<std::endl;
    }
    //setear fuente de texto
    TTF_Font* font = TTF_OpenFont("fonts/mula.otf",20);

    //comprobar que sdl2 y sdl2-ttf carguen
    engine::Engine engine;

    //evento
    SDL_Event ev;
    SDL_Event input;

    pl::Player player(ev,renderer);
    
    SDL_Color colorT = {255,255,255};
    SDL_Color colorB = {0,255,0};
    
    int lf;
    
    
    
    //bucle
    while(run){

        //std::cout<<engine.getFps()<<std::endl;
        std::cout<<lf<<std::endl;
        while(SDL_PollEvent(&ev) != 0){
            if(ev.type == SDL_QUIT){
                run = false;
            }
            else if(ev.type == SDL_KEYDOWN){
                if(ev.key.keysym.sym == SDLK_ESCAPE){
                    run = false;
                }
                
            }
            player.processEvents(ev);
        }
        
        engine.update();
        player.update();

        lf = player.getLeftBullets();
        std::string leftbulletsT = std::to_string(lf);


        if (lf <= 5){
            colorB = {255,0,0};
        }
        else{
            colorB = {0,255,0};
        }

        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);

        engine.text(font,renderer,"bamoki engine V0.0.1", colorT, 20, 20);
        engine.text(font,renderer,"balas: " + leftbulletsT, colorB, 20, 40);
        

        player.render();
        
        SDL_RenderPresent(renderer);
    }
    engine.destroy_engine(window,renderer);
    return 0;

}