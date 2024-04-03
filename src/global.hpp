#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <iostream>
#include <SDL.h>

#include "bullet.hpp"

namespace glo{
    class Global{
        public:
            void bulletOutOfScreen(std::vector<bl::Bullet>&bullets ,int width, int height){
                
                auto x = bullets.begin();
                while(x != bullets.end()){
                    if(x->isOutOfBound(width,height)){
                        x = bullets.erase(x);
                    }
                    else{
                        ++x;
                    }
                }

            }
        private:
    };
}

#endif