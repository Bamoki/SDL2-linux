#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

namespace engine{
    class Engine{
        public:
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
            
    };
}
