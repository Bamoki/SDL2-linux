#include <SDL.h>
#include <iostream>

#include "bullet.hpp"


namespace ey{
    class Enemy{
        public:
            Enemy(SDL_Renderer* renderer) : renderer(renderer){
                enemyR.h = 50;
                enemyR.w = 30;
                enemyR.y = 100;
                enemyR.x = 500;

                cooldownTime = 600;
                timeSinceLastShoot = cooldownTime;
                lastFrameTime = SDL_GetTicks();

                cooldownUp = 1000;
                timeSinceMoveUp = cooldownUp;

                cooldownDown = 5000;
                timeSinceMoveDown= cooldownDown;

                moveDown = false;
                moveUp = false;
                
            }

            void shoot(){
                
                for(auto& bullet:bullets){
                    if(!bullet.isFired()){
                        bullet.shoot();
                        break;
                    }
                }

                float bulletY = enemyR.y + enemyR.h / 2;
                bl::Bullet bullet(startX + enemyR.w,bulletY,speedb);
                bullets.push_back(bullet);
            }

            void update(){
                startX = enemyR.x -10;
                Uint32 currentTime = SDL_GetTicks();
                deltaTime = currentTime - lastFrameTime;
                lastFrameTime = currentTime;

                timeSinceLastShoot += deltaTime;
                timeSinceMoveUp += deltaTime;
                timeSinceMoveDown += deltaTime;

                move();
                global.bulletOutOfScreen(bullets,740,540);
                
            }
            void render(){
                SDL_SetRenderDrawColor(renderer,250,0,0,250);
                SDL_RenderFillRect(renderer,&enemyR);

                for(auto& bullet:bullets){
                    bullet.render(renderer);
                }
            }
            void move(){
                
                //std::cout<<"up: " << moveUp<< std::endl;
                //std::cout<<"down: "<< moveDown<<std::endl;
                //std::cout<<"time since last shoot: "<<timeSinceLastShoot<<std::endl;

                if(timeSinceLastShoot >= cooldownTime){
                    shoot();
                    timeSinceLastShoot = 0;
                    
                }
            
                /*if(timeSinceMoveDown >= cooldownDown){
                    moveUp = false;
                    moveDown = true;
                    timeSinceMoveDown = 0;
                }

                if(timeSinceMoveUp >= cooldownUp){
                    moveUp = true;
                    moveDown = false;
                    timeSinceMoveUp = 0;
                }   */

                // Movement of bullets
                for(auto& bullet:bullets){
                    bullet.move(false,enemyR);
                }
                
                

                // Movement of enemy
                if(moveDown == true){
                    enemyR.y += 1;
                }
                if(moveUp == true){
                    enemyR.y -= 1;
                }
            }
        private:
            SDL_Renderer* renderer;
            SDL_Rect enemyR;

            Uint32 deltaTime;
            Uint32 timeSinceLastShoot;
            Uint32 cooldownTime;
            Uint32 lastFrameTime;
            Uint32 timeSinceMoveUp;
            Uint32 timeSinceMoveDown;
            Uint32 cooldownUp;
            Uint32 cooldownDown;
        
            std::vector<bl::Bullet> bullets;
            float speedb = 3.0f;
            float startX, startY;

            bool moveUp;
            bool moveDown;
    };
}