#include "Animator.h"

Animator::Animator(char **filenames, int numFrames)
{
    for(int i=0; i<numFrames; i++){
        this->frames[i] = IMG_Load(filenames[i]);
    }
    this->numFrames = numFrames;
    this->currentFrame = 0;
}

SDL_Surface* Animator::nextFrame(){
    this->currentFrame++;
    if(this->currentFrame>=numFrames)
        this->currentFrame = 0;
    return this->frames[this->currentFrame];
}

SDL_Surface* Animator::prevFrame(){
    this->currentFrame--;
    if(this->currentFrame<=0)
        this->currentFrame = this->numFrames-1;
    return this->frames[this->currentFrame];

}

Animator::~Animator()
{
    //dtor
}
