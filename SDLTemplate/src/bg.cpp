#include "bg.h"

bg::bg(char* filename, int w)
{
    this->bgImage = IMG_Load(filename);
    this->width = w;
    this->srcrect.x = 10;
    this->srcrect.y = 5;
    this->srcrect.w = 160;
    this->srcrect.h = 125;
    this->dstrect.x = 0;
    this->dstrect.y = 0;
    this->dstrect.w = 300;
    this->dstrect.h = 260;
    this->currentStage = 1;
}

int bg::getWidth()
{
    return this->width;
}

void bg::setWidth(int w)
{
    this->width = w;
    this->srcrect.w = w;
}

int bg::getInitialWidth()
{
    return this->initialWidth;
}

void bg::setInitialWidth(int w)
{
    this->initialWidth = w;
}

int bg::getSrcRectX(){
    return this->srcrect.x;
}

void bg::setSrcRectX(int xPos){
    this->srcrect.x = xPos;
}

SDL_Rect* bg::getSrcrect()
{
    return &this->srcrect;
}

SDL_Rect* bg::getDstrect()
{
    return &this->dstrect;
}

SDL_Surface* bg::getBgImage()
{
    return this->bgImage;
}

void bg::setBgImage(const char* filename)
{
    this->bgImage = IMG_Load(filename);
}

bool bg::checkStageCollision(SDL_Rect* dstRect){
    SDL_Rect realObject;
    bool collisions = false;
    realObject.x = (dstRect->x/1.875)+this->getSrcRectX()-16;
    realObject.w = dstRect->w/1.875;
    realObject.y = dstRect->y/2.08-15;
    realObject.h = dstRect->h/2.08;
    std::cout << realObject.y << std::endl;
    switch(this->currentStage){
        case 1:
                if((realObject.y>(100-32))&&(realObject.y<=100+32)&&(realObject.x>=(0-32))&&(realObject.x<=0+833-20)){
                   collisions = true;
                }

                if((realObject.y>(84-32))&&(realObject.y<=84+16)&&(realObject.x>=(290-32))&&(realObject.x<=290+144-20)){
                   collisions = true;
                }

                if((realObject.y>=(36-32))&&(realObject.y<=36+64)&&(realObject.x>=(561-32))&&(realObject.x<=561+32-20)){
                    collisions = true;
                }

                if((realObject.y>=(84-32))&&(realObject.y<=84+16)&&(realObject.x>=(785-32))&&(realObject.x<=785+48-20)){
                    collisions = true;
                }

                if((realObject.y>=(68-32))&&(realObject.y<=68+16)&&(realObject.x>=(801-32))&&(realObject.x<=801+32-20)){
                    collisions = true;
                }

                if((realObject.y>=(68-32))&&(realObject.y<=68+16)&&(realObject.x>=(865-32))&&(realObject.x<=865+48-20)){
                    collisions = true;
                }
                if((realObject.y>=(84-32))&&(realObject.y<=84+16)&&(realObject.x>=(865-32))&&(realObject.x<=865+64-20)){
                    collisions = true;
                }

                if((realObject.y>=(100-32))&&(realObject.y<=100+32)&&(realObject.x>=(865-32))&&(realObject.x<=865+401-20)){
                    collisions = true;
                }

                if((realObject.y>=(68-32))&&(realObject.y<=68+16)&&(realObject.x>=(11690-32))&&(realObject.x<=1169+102-20)){
                    collisions = true;
                }
                if((realObject.y>=(84-32))&&(realObject.y<=84+16)&&(realObject.x>=(1201-32))&&(realObject.x<=1201+80-20)){
                    collisions = true;
                }
                return collisions;
        default: return false;
    }
}

int bg::getCurrentStage(){
    return this->currentStage;
}

bg::~bg()
{
    //dtor
}
