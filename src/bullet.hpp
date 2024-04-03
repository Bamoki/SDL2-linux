#ifndef BULLET_HPP
#define BULLET_HPP

#include <SDL.h>
#include <iostream>
#include <vector>


namespace bl{
    class Bullet{
            
        public:

            Bullet(float startX, float startY, float bulletSpeed) : x(startX), y(startY), bulletSpeed(bulletSpeed) {
                bulletR.h = 20;
                bulletR.w = 10;
                bulletR.x = 0;
                bulletR.y = 0;

            }

            void move(bool Right,SDL_Rect Rect){
                
                if(fired) {
                    if(Right == true){
                        x += bulletSpeed;
                        bulletR.x = static_cast<int>(x);
                    }
                    if(Right == false){
                        x -= bulletSpeed;
                        bulletR.x = static_cast<int>(x);
                    }
                    
                    
                }
                
                bulletR.y = y;
                
            }

            void shoot(){
                fired = true;
                
            }

            bool isFired() const{
                return fired;
            }

            

            void render(SDL_Renderer* renderer){
                SDL_SetRenderDrawColor(renderer,255,0,0,255);
                SDL_RenderFillRect(renderer,&bulletR);
            }

            bool isOutOfBound(int width, int height){
                return (x<0 || x > width || y < 0 || y > height);
            }

        private:
            std::vector<Bullet> bullets;
            float x,y,bulletSpeed;
            SDL_Rect bulletR;
            bool fired;
    };
}

#endif