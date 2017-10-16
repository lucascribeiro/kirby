#ifndef ENEMY_H
#define ENEMY_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <bg.h>
#include <math.h>
class enemy
{
    public:
        enemy(int type, float x, float y);
        enemy();
        int getType();
        void initialize(int type, float x, float y);
        void movement(bg* stage);
        SDL_Rect* getSrcRect();
        SDL_Rect* getDstRect();
        SDL_RendererFlip getFlip();
        virtual ~enemy();

    protected:

    private:
        SDL_Rect srcRect;
        SDL_Rect dstRect;
        SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
        float xPos;
        float yPos;
        float speed;
        int repeat = 0;
        int type;
};

#endif // ENEMY_H
