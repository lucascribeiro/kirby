#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <bg.h>

using namespace std;

int main(int argc, char *argv[])
{
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        cout << "Unable to init SDL: " << SDL_GetError() << endl;
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 600, 200, SDL_WINDOW_SHOWN);
    if (!win)
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!ren)
    {
        SDL_DestroyWindow(win);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // load an image
    /*SDL_Surface* bmp = IMG_Load("cb.bmp"); //SDL_LoadBMP("cb.bmp");
    if (!bmp)
    {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        cout << "Unable to load bitmap: " << SDL_GetError() << endl;
        return 1;
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp);
    if(!tex)
    {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << endl;
        return 1;
    }
    */
    // centre the bitmap on screen
    SDL_Rect srcrect, dstrect;
    int w, h;
    SDL_GetWindowSize(win, &w, &h);
    bg stage("sprites/stage1.gif", 1760);
    SDL_Texture *bgTex = SDL_CreateTextureFromSurface(ren, stage.getBgImage());
    SDL_FreeSurface(stage.getBgImage());
    // program main loop
    bool done = false;
    while (!done)
    {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    break;
                }
            } // end switch
        } // end of message processing
        // DRAWING STARTS HERE

        // clear screen
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, bgTex, stage.getSrcrect(), stage.getDstrect());
        SDL_RenderPresent(ren);

        // DRAWING ENDS HERE

    } // end main loop

    // free loaded bitmap
    SDL_DestroyTexture(bgTex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);

    // all is well ;)
    cout << "Exited cleanly" << endl;
    return 0;
}
