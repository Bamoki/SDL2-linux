#include <SDL.h>
#include <iostream>
#include <vector>


namespace bl{
    class Bullet{
            
        public:

            Bullet(float startX, float startY, float bulletSpeed) : x(startX), y(startY), bulletSpeed(bulletSpeed) {
                bulletR.h = 20;
                bulletR.w = 10;
                //startX = bulletR.x;
                //startY = bulletR.y;
                bulletR.x = 200;
                bulletR.y = 100;
            }

            void move(SDL_Rect player){
                std::cout<<"x bala = "<< bulletR.x<< " / " <<"y bala = " << bulletR.y << std::endl;
                
                if(!fired){
                    x += bulletSpeed;
                    bulletR.x = static_cast<int>(x);
                    
                }
                
                
            }

            void shootBullet(SDL_Rect Player){
                bullets.emplace_back(x,Player.y,bulletSpeed);
            }

            void shoot(){
                fired = true;
            }

            void render(SDL_Renderer* renderer){
                SDL_SetRenderDrawColor(renderer,255,0,0,255);
                SDL_RenderFillRect(renderer,&bulletR);
            }

        private:
            std::vector<Bullet> bullets;
            float x,y,bulletSpeed;
            SDL_Rect bulletR;
            bool fired = false;
    };
}