#include "kirby.h"

kirby::kirby()
{
    this->spriteSheet = IMG_Load("sprites/kirby.png");
    this->xPos = 60;
    this->yPos = 168;
    this->dstRect.x = 60;
    this->dstRect.y = 168;
    this->dstRect.w = 32;
    this->dstRect.h = 32;
    //ctor
}

void kirby::initialize(){
    this->state = STANDING;
    this->previousState = STANDING;
    this->srcRect.x = 2;
    this->srcRect.y = 11;
    this->srcRect.w = 16;
    this->srcRect.h = 16;
}

void kirby::stand(){
    this->state = STANDING;
    this->previousState = STANDING;
    this->srcRect.x = 2;
    this->srcRect.y = 11;

}

int kirby::sceneCollision(bg* stage){
    SDL_Rect** stageBorders = stage->getStageBoxes();
    int borderAmount = stage->getBorderAmount();
    int collisions = 0;
    SDL_Rect realKirby;
    realKirby.x = (this->dstRect.x/1.875)+stage->getSrcRectX();
    realKirby.w = this->dstRect.w/1.875;
    realKirby.y = this->dstRect.y/2.08;
    realKirby.h = this->dstRect.h/2.08;
    for(int i=0;i<borderAmount;i++){
        if((realKirby.y >= stageBorders[i]->y-32)&&(realKirby.y <= stageBorders[i]->y+stageBorders[i]->h)){
            collisions = collisions|HORIZONTAL_COLLISION;
            std::cout << stageBorders[i]->x;
        }
        if((realKirby.x >= stageBorders[i]->w-32)&&(realKirby.x <= stageBorders[i]->x+stageBorders[i]->w)){
            collisions = collisions|VERTICAL_COLLISION;
        }
    }
    return collisions;
}

void kirby::setState(int state){
    this->state = state;
}

int kirby::getState(){
    return this->state;
}

int kirby::getPreviousState(){
    return this->previousState;
}

void kirby::jump(){
    if(this->previousState!=JUMPING)
        this->repeat = 0;
    this->previousState = JUMPING;
    this->srcRect.x = 2;
    this->srcRect.y = 45;
    if(repeat>60)
        this->srcRect.x = 19;
    this->repeat++;
    std::cout << repeat << std::endl;

}

void kirby::changeDstRect(float xChange, float yChange, bg* stage){
    if(xChange>0){
        if((this->dstRect.x>134)&&stage->getSrcRectX()<(stage->getWidth()-159)){
            stage->xPos+=xChange;
            stage->setSrcRectX(stage->xPos);
        }else{
            this->xPos+=xChange;
        }
    }else if (xChange<3){
        if((this->dstRect.x<134)&&stage->getSrcRectX()>0){
            stage->xPos+=xChange;
            stage->setSrcRectX(stage->xPos);
        }else{
            this->xPos+=xChange;
        }
    }

    this->yPos-=yChange;
    this->dstRect.x = (int)xPos;
    this->dstRect.y = (int)yPos;
}

void kirby::walk(){
    this->state = WALKING;
    this->repeat = (repeat+1)%5;
    if(this->repeat==0){
        if(this->previousState==WALKING){
            this->step = (step+1)%4;
            this->srcRect.x = this->walking[step];
        }
        else{
            previousState = WALKING;
            this->srcRect.y = 28;
            this->step = 0;
            this->srcRect.x = 19;
        }
    }
}

SDL_Surface* kirby::getSpriteSheet(){
    return this->spriteSheet;
}

SDL_Rect* kirby::getSrcRect(){
    return &this->srcRect;
}

SDL_Rect* kirby::getDstRect(){
    return &this->dstRect;
}

kirby::~kirby()
{
    //dtor
}
