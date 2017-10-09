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

void kirby::crawl(){
    this->state = CRAWL;
    this->previousState = CRAWL;
    this->srcRect.x = 36;
    this->srcRect.y = 11;
}

void kirby::squish(bool start){
    this->state = SQUISH;
    if(start){
        this->repeat = 0;
    }
    this->srcRect.x = 19;
    this->srcRect.y = 11;
    this->repeat++;
    if(repeat>4){
        this->state = this->previousState;
    }
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
}

void kirby::inflate(){
    if(this->previousState!=INFLATED){
        this->repeat=0;
        this->srcRect.x = 2;
        this->srcRect.y = 62;
        this->srcRect.h = 24;
        this->state = INFLATED;
        this->previousState = INFLATED;
    }
    if(repeat <=2){
        this->srcRect.x = 19;
        this->srcRect.y = 62;
        this->srcRect.h = 24;
        this->dstRect.h = 48;
        this->dstRect.y-=4;
        this->yPos-=4;
    }else{
        if(repeat <= 4){
            this->srcRect.x = 36;
            this->srcRect.y = 62;
            this->srcRect.w = 23;
            this->dstRect.w = 48;
        }else{
            if((repeat-5)%10<5){
                this->srcRect.x = 60;
                this->srcRect.y = 62;
            }else{
                this->srcRect.x = 84;
                this->srcRect.y = 62;
            }
        }
    }
    repeat++;

}

bool kirby::deinflate(){
    if(this->previousState = INFLATED){
        repeat = 0;
    }
    if(repeat<=2){
        this->srcRect.x = 108;
        this->srcRect.y = 62;
        repeat++;
        return false;
    }
    if(repeat<=4){
        this->srcRect.x = 132;
        this->srcRect.y = 62;
        repeat++;
        return false;
    }
    if(repeat<=6){
        this->state = JUMPING;
        this->srcRect.h = 16;
        this->srcRect.w = 16;
        repeat++;
        return false;
    }
    return true;
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

void kirby::hit(enemy* e){
    if(this->dstRect.x<=e->getDstRect()->x+32 && this->dstRect.x>=e->getDstRect()->x-31){
        if(currentlyHit==0)
            this->currentlyHit = 1;
            this->lives--;
            //std::cout << this->lives << std::endl;
    }
}

void kirby::isHit(){
    if(this->currentlyHit>0){
        if(currentlyHit%4<2){
            this->srcRect.h = 0;
        }else{
            this->srcRect.h = 16;
        }
        this->currentlyHit++;
        if(this->currentlyHit>46)
            this->currentlyHit = 0;
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

void kirby::setDstRectX(int x){
    this->dstRect.x = x;
}
kirby::~kirby()
{
    //dtor
}
