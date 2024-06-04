#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <sstream>

#include "bullet.hpp"
#include "global.hpp"
#include <SDL_scancode.h>
#include "collision.hpp"

glo::Global global;

namespace pl
{
    class Player
    {

    public:
        Player(SDL_Renderer *renderer) : renderer(renderer){

            up = false;
            down = false;
            playerR.x = 100;
            playerR.y = 200;
            playerR.h = 50;
            playerR.w = 30;

            startX = playerR.x;
            startY = playerR.y;

            cooldownTime = 200;
            timeSinceLastShoot = cooldownTime;
            lastFrameTime = SDL_GetTicks();
        }

        void shoot(){

            for(auto& bullet:bullets){
                if(!bullet.isFired()){
                    bullet.shoot();
                    break;
                }
                
            }

            float bulletY = playerR.y + playerR.h / 2;

            bl::Bullet bullet(startX + playerR.w, bulletY, speedb);
            
            bullets.push_back(bullet);

        }

        void processEvents(SDL_Event ev)
        {

            const Uint8 *Keystates = SDL_GetKeyboardState(NULL);

            up = false;
            down = false;
            if (Keystates[SDL_SCANCODE_W])
            {
                up = true;
                down = false;
            }

            if (Keystates[SDL_SCANCODE_S])
            {
                down = true;
                up = false;
            }

            if (Keystates[SDL_SCANCODE_SPACE])
            {
                if(timeSinceLastShoot >= cooldownTime && leftbullets >= 1){
                    shoot();
                    timeSinceLastShoot = 0;
                    leftbullets -= 1;
                }   
                
            }

            if (Keystates[SDL_SCANCODE_1] )
            {
                
                leftbullets += 10;
                
            }
        }

        void update()
        {
            
            Uint32 currentTime = SDL_GetTicks();
            deltaTime = currentTime - lastFrameTime;
            lastFrameTime = currentTime;

            timeSinceLastShoot += deltaTime;


            x = playerR.x;
            y = playerR.y;
            if (up == true)
            {
                playerR.y -= 10;
            }
            if (down == true)
            {
                playerR.y += 10;
            }

            for (auto &bullet : bullets)
            {
                bullet.move(true,playerR);
            }

            global.bulletOutOfScreen(bullets,740,540);
            
        }

        void render()
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &playerR);

            for (auto &bullet : bullets)
            {
                bullet.render(renderer,0,255,0,255);
            }
        }

        int getLeftBullets(){
            return leftbullets;
        }


        bool handleBulletCollisions(const SDL_Rect& targetRect) {
            for (auto& bullet : bullets) {
                if (bullet.isFired() && checkCollision(bullet.getRect(), targetRect)) {
                    bullet.reset();
                    
                    return true; // Colisión detectada
                }
            }
            return false;
        }

        SDL_Rect getRect() const {
            return playerR;
        }
    private:
        float speedb = 10.0f;
        std::vector<bl::Bullet> bullets;

        SDL_Rect playerR;
        bool up;
        bool down;
        SDL_Renderer *renderer;
        float startX, startY;
        int x;
        int y;
        int leftbullets = 10;

        Uint32 deltaTime;
        Uint32 timeSinceLastShoot;
        Uint32 cooldownTime;
        Uint32 lastFrameTime;
    };
}