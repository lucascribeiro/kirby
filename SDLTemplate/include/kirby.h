#ifndef KIRBY_H
#define KIRBY_H
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <bg.h>
#include "enemy.h"
const int STANDING = 1;
const int WALKING = 2;
const int JUMPING = 3;
const int INFLATED = 4;
const int INHALED = 5;
const int CRAWL = 6;
const int SQUISH = 7;
const int DEINFLATE = 8;

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
        bool deinflate();
        void crawl();
        void squish(bool start);
        SDL_Rect* getSrcRect();
        SDL_Rect* getDstRect();
        void changeDstRect(float xChange, float yChange, bg* stage);
        void setDstRect(float x, float y);
        void setDstRectX(int x);
        void hit(enemy* e);
        void isHit();
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
        int currentlyHit = 0;
        int walking[4] = {2,19,36,53};
        int lives = 6;
        int points = 0;
};

#endif // KIRBY_H
