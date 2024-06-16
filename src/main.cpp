#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string.h>

#include "engine.cpp"
#include "player.hpp"
#include "enemy.hpp"
#include "collision.hpp"

//variables
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Rect text;

bool run = false;
bool startGame = false;

int main(int argc, char* args[]){

    //iniciar sdl2, si inicia bien que se cree la ventana
    if(SDL_Init(SDL_INIT_EVERYTHING) >= 0){
        window = SDL_CreateWindow("game",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,740,540,SDL_WINDOW_SHOWN);
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

    pl::Player player(renderer);
    
    SDL_Color colorT = {255,255,255};
    SDL_Color colorB = {0,255,0};
    SDL_Color colorF = {0,255,0};
    
    int lf;
    int fps = engine.getFps();
    

    ey::Enemy enemy(renderer);

    while (startGame == false){
        
         while(SDL_PollEvent(&ev) != 0){
            if(ev.type == SDL_QUIT){
                run = false;
            }
            else if(ev.type == SDL_KEYDOWN){
                if(ev.key.keysym.sym == SDLK_ESCAPE){
                    run = false;
                }
            }
            if(ev.type == SDL_KEYDOWN and startGame == false){
                if(ev.key.keysym.sym == SDLK_e){
                    startGame = true;
                    run = true;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer,100,150,0,255);
        SDL_RenderClear(renderer);

        engine.text(font,renderer,"Controles: ", colorT, 100, 100);
        engine.text(font,renderer,"Subir: W", colorT, 120, 120);
        engine.text(font,renderer,"Bajar: S", colorT, 120, 140);
        engine.text(font,renderer,"Disparar: ESPACIO", colorT, 120, 160);

        engine.text(font,renderer,"Presione E para empezar", colorT, 250, 500);

        SDL_RenderPresent(renderer);
    }
    
    //bucle juego
    while(run){

        while(SDL_PollEvent(&ev) != 0){
            if(ev.type == SDL_QUIT){
                run = false;
            }
            else if(ev.type == SDL_KEYDOWN){
                if(ev.key.keysym.sym == SDLK_ESCAPE){
                    run = false;
                }
            }
            if(ev.type == SDL_KEYDOWN and startGame == false){
                if(ev.key.keysym.sym == SDLK_SPACE){
                    startGame = true;
                    
                }
            }
            player.processEvents(ev);
        }
        
        // Update
        engine.update();
        player.update();
        enemy.update();

        lf = player.getLeftBullets();
        fps = engine.getFps();
        
        std::string leftbulletsT = std::to_string(lf);
        std::string fpsT = std::to_string(engine.getFps());
        std::string healthPlayerT = std::to_string(player.getHealth());


        if (lf <= 5){
            colorB = {255,0,0};
        }
        else{
            colorB = {0,255,0};
        }
        if (fps <= 30){
            colorF = {255,0,0};
        }
        else{
            colorF = {0,255,0};
        }
        
        /* Verificar colisiones
        if (player.handleBulletCollisions(enemy.getRect())) {
            std::cout << "El enemigo ha sido alcanzado!" << std::endl;
        }
        */
        if (enemy.handleBulletCollisions(player.getRect())) {
            player.hit();
            std::cout<<player.getHealth()<<std::endl;
            if(player.getHealth() <= -1){
                run = false;
            }
        }



        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);

        // Texto en pantalla
        engine.text(font,renderer,"bamoki engine V0.0.4", colorT, 20, 20);
        engine.text(font,renderer,"balas: " + leftbulletsT, colorB, 20, 40);
        engine.text(font,renderer,"fps: " + fpsT, colorF, 20, 60);
        engine.text(font,renderer,"vida jugador: " + healthPlayerT,colorT,400,20);
        
        // Render
        player.render();
        enemy.render();
        
        SDL_RenderPresent(renderer);
    }
    engine.destroy_engine(window,renderer);
    return 0;
}