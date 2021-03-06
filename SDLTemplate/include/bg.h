#ifndef BG_H
#define BG_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class bg
{
    public:
        bg(char* filename, int w);
        virtual ~bg();
        int getWidth();
        void setWidth(int w);
        int getInitialWidth();
        void setInitialWidth(int w);
        SDL_Rect* getSrcrect();
        int getSrcRectX();
        int getCurrentStage();
        void setSrcRectX(int xPos);
        SDL_Rect* getDstrect();
        SDL_Surface* getBgImage();
        void setBgImage(const char* filename);
        bool checkStageCollision(SDL_Rect* object);
        float xPos = 0;
    protected:

    private:
    SDL_Surface *bgImage;
    SDL_Rect* stageBoxes;
    SDL_Rect srcrect;
    SDL_Rect dstrect;
    int currentStage;
    int width;
    int initialWidth;
};

#endif // BG_H
