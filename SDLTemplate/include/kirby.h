#ifndef KIRBY_H
#define KIRBY_H
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <bg.h>
const int STANDING = 1;
const int WALKING = 2;
const int JUMPING = 3;
const int INFLATED = 4;
const int INHALED = 5;
const int CRAWL = 6;
const int VERTICAL_COLLISION = 2;
const int HORIZONTAL_COLLISION = 1;

class kirby
{
    public:
        kirby();
        void initialize();
        void stand();
        void jump();
        void walk();
        void inhale();
        void inflate();
        void crawl();
        int sceneCollision(bg* stage);
        SDL_Rect* getSrcRect();
        SDL_Rect* getDstRect();
        void changeDstRect(float xChange, float yChange, bg* stage);
        void setDstRect(float x, float y);
        void hit();
        void setState(int state);
        int getState();
        int getPreviousState();
        SDL_Surface* getSpriteSheet();
        virtual ~kirby();

    protected:


    private:
        SDL_Rect srcRect;
        SDL_Rect dstRect;
        float xPos;
        float yPos;
        SDL_Surface* spriteSheet;
        int previousState;
        int state;
        /*
        1 - standing
        2 - walking
        3 - jumping
        4 - inflated
        5 - inhaled
        6 - crawl
        */
        int step = 0;
        int repeat = 0;
        int walking[4] = {2,19,36,53};
        int lives;
        int points;
};

#endif // KIRBY_H
