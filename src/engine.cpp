#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <sstream>

namespace engine{
    class Engine{
        public:
        Engine(){
        
            lastFrameTime = SDL_GetTicks();
            frames = 0;
            fpsTimer = 0;
            fps = 0;
        }
    
        void update(){
            Uint32 currentTime = SDL_GetTicks();
            deltaTime = currentTime - lastFrameTime;
            lastFrameTime = currentTime;

            frames++;
            fpsTimer += deltaTime;

            if(fpsTimer >= 1000){
                fps = frames * 1000 / fpsTimer;
                frames = 0;
                fpsTimer = 0;
            }
            
        }

        void destroy_engine(SDL_Window* window, SDL_Renderer* renderer){
            SDL_DestroyWindow(window);
            SDL_DestroyRenderer(renderer);
            
            TTF_Quit();
            SDL_Quit();
        }
        void text(TTF_Font* font,SDL_Renderer* render,const std::string& Text,SDL_Color colorT,int x,int y){
            SDL_Surface* textS = TTF_RenderText_Solid(font,Text.c_str(),colorT);
            SDL_Texture* textT = SDL_CreateTextureFromSurface(render,textS);

            int textW = textS->w;
            int textH = textS->h;
            
            SDL_FreeSurface(textS);
            SDL_Rect destRect = {x,y,textW,textH};

            SDL_RenderCopy(render,textT,nullptr,&destRect);
            SDL_DestroyTexture(textT);
        }

        int getFps(){
            return fps;
        }

        

        private:
            Uint32 deltaTime;
            Uint32 lastFrameTime;
            Uint32 frames;
            Uint32 fpsTimer;
            int fps;
            
    };
}
