#include <SDL.h>
#include <iostream>

#include "bullet.hpp"
#include "collision.hpp"

namespace ey{
    class Enemy{
        public:
            Enemy(SDL_Renderer* renderer) : renderer(renderer){
                enemyR.h = 50;
                enemyR.w = 30;
                enemyR.y = 530;
                enemyR.x = 500;

                cooldownTime = 400;
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

                move();
                global.bulletOutOfScreen(bullets,740,540);
            }
            void render(){
                SDL_SetRenderDrawColor(renderer,250,0,0,250);
                SDL_RenderFillRect(renderer,&enemyR);

                for(auto& bullet:bullets){
                    bullet.render(renderer,255,0,0,255);
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
            
                if(enemyR.y == 530){
                    moveDown = true;
                    moveUp = false;

                }
                if(enemyR.y == 0){
                    moveUp = true;
                    moveDown = false;
                }

                // Movement of bullets
                for(auto& bullet:bullets){
                    bullet.move(false,enemyR);
                }      

                // Movement of enemy
                if(moveDown == true){
                    enemyR.y -= 5;
                }
                if(moveUp == true){
                    enemyR.y += 5;
                }
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
                return enemyR;
            }
        private:
            SDL_Renderer* renderer;
            SDL_Rect enemyR;

            Uint32 deltaTime;
            Uint32 timeSinceLastShoot;
            Uint32 cooldownTime;
            Uint32 lastFrameTime;
        
            std::vector<bl::Bullet> bullets;
            float speedb = 6.0f;
            float startX, startY;

            bool moveUp = false;
            bool moveDown = false;
    };
}