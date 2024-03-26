#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

#include "bullet.hpp"

namespace pl
{
    class Player
    {

    public:
        Player(SDL_Event ev, SDL_Renderer *renderer) : renderer(renderer)
        {

            up = false;
            down = false;
            playerR.x = 100;
            playerR.y = 100;
            playerR.h = 50;
            playerR.w = 30;
            processEvents(ev);

            startX = playerR.x;
            startY = playerR.y;
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
                createBullet();
            }
        }

        void update()
        {
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
                bullet.move(playerR);
            }
        }

        void render()
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &playerR);

            for (auto &bullet : bullets)
            {
                bullet.render(renderer);
            }
        }

    private:
        float speedb = 3.0f;
        std::vector<bl::Bullet> bullets;
        void createBullet()
        {
            bl::Bullet bullet(startX, startY, speedb);
            bullets.push_back(bullet);
            bullets.back().shoot();
        }

        SDL_Rect playerR;
        bool up;
        bool down;
        SDL_Renderer *renderer;
        float startX, startY;
        int x;
        int y;
    };
}
