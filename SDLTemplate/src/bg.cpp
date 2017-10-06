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

void bg::setStageBoxes(){
    SDL_Rect* boxes;
    SDL_Rect* box;
    switch(this->currentStage){
        case 1: box = new SDL_Rect;
                box->x = 0;
                box->y = 100;
                box->h = 32;
                box->w = 833;
                boxes[0] = box*;
                box = new SDL_Rect;
                box->x = 290;
                box->y = 84;
                box->h = 16;
                box->w = 42;
                boxes[1] = box*;box = new SDL_Rect;
                box->x = 561;
                box->y = 36;
                box->h = 64;
                box->w = 32;
                boxes[2] = box*;box = new SDL_Rect;
                box->x = 785;
                box->y = 84;
                box->h = 16;
                box->w = 48;
                boxes[3] = box*;box = new SDL_Rect;
                box->x = 801;
                box->y = 68;
                box->h = 16;
                box->w = 32;
                boxes[4] = box*;box = new SDL_Rect;
                box->x = 865;
                box->y = 68;
                box->h = 16;
                box->w = 48;
                boxes[5] = box*;box = new SDL_Rect;
                box->x = 865;
                box->y = 84;
                box->h = 16;
                box->w = 64;
                boxes[6] = box*;box = new SDL_Rect;
                box->x = 865;
                box->y = 100;
                box->h = 32;
                box->w = 401;
                boxes[7] = box*;box = new SDL_Rect;
                box->x = 1169;
                box->y = 68;
                box->h = 16;
                box->w = 102;
                boxes[8] = box*;box = new SDL_Rect;
                box->x = 1201;
                box->y = 84;
                box->h = 16;
                box->w = 80;
                boxes[9] = box*;
                this->stageBoxes = boxes;
        default: this->stageBoxes == NULL;
    }
}

SDL_Rect* bg::getStageBoxes(){
    return this->stageBoxes;
}

int bg::getBorderAmount(){
    switch(currentStage){
        case 1: return 10;
        default: return 0;
    }

}

bg::~bg()
{
    //dtor
}
