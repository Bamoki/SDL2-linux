#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <SDL.h>

bool checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
    return SDL_HasIntersection(&a, &b);
}

#endif // COLLISION_HPP