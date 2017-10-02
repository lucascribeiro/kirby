#ifndef ANIMATOR_H
#define ANIMATOR_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Animator
{
    public:
        Animator(char *filename, int positions[2][] int numFrames);
        virtual ~Animator();
        SDL_Surface *nextFrame();
        SDL_Surface *prevFrame();

    protected:

    private:
        SDL_Surface* frames;
        int numFrames;
        int currentFrame;
};

#endif // ANIMATOR_H
