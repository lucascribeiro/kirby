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
    int frames = 0;
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
        case 2:     frames = 120;
                    this->xPos = this->xPos + (float)pow(-1.0, (repeat+frames)/frames)*0.4;
                    this->dstRect.x = (((int)this->xPos - stage->getSrcRectX())*300)/160;
                    this->dstRect.y = ((int)this->yPos*260)/125;
                    repeat++;
                    if(repeat%(2*frames)<frames){
                        this->flip = SDL_FLIP_HORIZONTAL;
                    }                    else{
                        this->flip = SDL_FLIP_NONE;
                    }
                    if(repeat%10<5){
                        this->srcRect.x = 8;
                        this->srcRect.y = 22;
                    }else{
                        this->srcRect.x = 26;
                        this->srcRect.y = 22;
                    }
                    break;
        case 3:     this->xPos -=0.4;
                    this->dstRect.x = (((int)this->xPos - stage->getSrcRectX())*300)/160;
                    this->dstRect.y = ((int)this->yPos*260)/125;
                    repeat++;
                    if(repeat%10<5){
                        this->srcRect.x = 120;
                        this->srcRect.y = 22;
                    }else{
                        this->srcRect.x = 139;
                        this->srcRect.y = 22;
                    }
                    break;

        case 4:     frames=30;
                    repeat++;
                    if(repeat%(2*frames)==1){
                        this->speed = 0;
                    }
                    if(repeat%(2*frames)==frames){
                        this->speed = 50;
                    }
                    this->yPos -=speed*1.0/30.0;
                    this->dstRect.x = (((int)this->xPos - stage->getSrcRectX())*300)/160;
                    this->dstRect.y = ((int)this->yPos*260)/125;
                    if(repeat%(2*frames)<frames){
                        this->srcRect.x = 102;
                        this->srcRect.y = 22;
                    }else{
                        speed-=50.0/(frames/2);

                        if(repeat%10<5){
                            this->srcRect.x = 120;
                            this->srcRect.y = 22;
                        }else{
                            this->srcRect.x = 139;
                            this->srcRect.y = 22;
                        }
                    }
                    break;
        case 5:     frames = 90;
                    this->yPos = this->yPos + (float)pow(-1.0, (repeat+frames)/frames)*0.6;
                    this->dstRect.x = (((int)this->xPos - stage->getSrcRectX())*300)/160;
                    this->dstRect.y = ((int)this->yPos*260)/125;
                    repeat++;
                    if(repeat%10<5){
                        this->srcRect.x = 158;
                        this->srcRect.y = 22;
                    }else{
                        this->srcRect.x = 177;
                        this->srcRect.y = 22;
                    }
                    break;
        case 6:     if(this->repeat%119==0){
                        this->speed = 20;
                    }
                    this->yPos -= this->speed/30.0;
                    this->xPos -= 0.4;
                    this->speed-= (20.0/60.0);
                    this->dstRect.x = (((int)this->xPos - stage->getSrcRectX())*300)/160;
                    this->dstRect.y = ((int)this->yPos*260)/125;
                    repeat++;
                    if(repeat%10<5){
                        this->srcRect.x = 158;
                        this->srcRect.y = 22;
                    }else{
                        this->srcRect.x = 177;
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
    this->srcRect.h = 16;
    this->srcRect.w = 16;
    if(this->type==4)
        this->speed = 0;
}

SDL_RendererFlip enemy::getFlip(){
    return this->flip;
}

enemy::~enemy()
{
    //dtor
}
