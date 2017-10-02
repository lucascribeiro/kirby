#include "bg.h"

bg::bg(char* filename, int w)
{
    this->bgImage = IMG_Load(filename);
    this->width = w;
    this->srcrect.x = 100;
    this->srcrect.y = 5;
    this->srcrect.w = 160;
    this->srcrect.h = 125;
    this->dstrect.x = 0;
    this->dstrect.y = 0;
    this->dstrect.w = 300;
    this->dstrect.h = 260;

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

bg::~bg()
{
    //dtor
}
