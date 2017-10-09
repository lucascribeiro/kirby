#include "enemy.h"

enemy::enemy(int type, float x, float y)
{
    this->type = type;
    this->xPos = x;
    this->yPos = y;
    this->dstRect.h = 32;
    this->dstRect.w = 32;
    switch (this->type){
        case 1:     this->srcRect.h = 16;
                    this->srcRect.w = 16;
                    break;
        case 2:     this->srcRect.x = 8;
                    this->srcRect.y = 23;
                    this->srcRect.h = 15;
                    this->srcRect.w = 15;
                    break;
        default:    break;
    }
}

enemy::enemy(){
    this->dstRect.h = 32;
    this->dstRect.w = 32;
}

void enemy::movement(bg* stage){
    switch(this->type){
        case 1:     this->xPos -=0.4;
                    this->dstRect.x = (((int)this->xPos - stage->getSrcRectX())*300)/160;
                    this->dstRect.y = ((int)this->yPos*260)/125;
                    repeat++;
                    if(repeat%10<5){
                        this->srcRect.x = 8;
                        this->srcRect.y = 22;
                    }else{
                        this->srcRect.x = 26;
                        this->srcRect.y = 22;
                    }
                    break;
        default:    break;
    }
}

SDL_Rect* enemy::getSrcRect(){
    return &this->srcRect;
}

SDL_Rect* enemy::getDstRect(){
    return &this->dstRect;
}

int enemy::getType(){
    return this->type;
}

void enemy::initialize(int type, float x, float y){
    this->type = type;
    this->xPos = x;
    this->yPos = y;
    switch (this->type){
        case 1:     this->srcRect.h = 15;
                    this->srcRect.w = 15;
                    break;
        case 2:     this->srcRect.x = 8;
                    this->srcRect.y = 23;
                    this->srcRect.h = 15;
                    this->srcRect.w = 15;
                    break;
        default:    break;
    }
}

enemy::~enemy()
{
    //dtor
}
