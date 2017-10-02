#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <bg.h>
#include <kirby.h>

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

    SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 300, 300, SDL_WINDOW_SHOWN);
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
    const int FPS = 30;
    const float maxSpeed = 0.4;
    const float accelAmount = 1.8;
    const float initialJumpSpeed = 6.0;
    const float gravity = 6.0;
    Uint32 fpsCounter;
    float speedx = 0;
    float speedy = 0;
    float accelx = 0;
    float accely = 0;
    int w, h;
    SDL_GetWindowSize(win, &w, &h);
    bg stage("sprites/stage1.gif", 1760);
    kirby player;
    player.initialize();
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_Texture *bgTex = SDL_CreateTextureFromSurface(ren, stage.getBgImage());
    SDL_Texture *playerTex = SDL_CreateTextureFromSurface(ren, player.getSpriteSheet());
    SDL_FreeSurface(stage.getBgImage());
    // program main loop
    bool done = false;
    while (!done)
    {
        fpsCounter = SDL_GetTicks();
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
                    if (event.key.keysym.sym == SDLK_ESCAPE){
                        done = true;
                        break;
                    }
                    if (event.key.keysym.sym == SDLK_UP);
                    if (event.key.keysym.sym == SDLK_DOWN);
                    if (event.key.keysym.sym == SDLK_LEFT){
                        accelx = -1;
                        break;
                    }
                    if (event.key.keysym.sym == SDLK_RIGHT){
                        accelx = 1;
                        break;
                    }
                    if (event.key.keysym.sym == SDLK_x){
                        if(player.getState()!=JUMPING)
                        {
                            accely = -1;
                            speedy = initialJumpSpeed;
                            player.setState(JUMPING);
                        }
                    }
                    if (event.key.keysym.sym == SDLK_c);
                    break;
                }
            case SDL_KEYUP:
            {
                if (event.key.keysym.sym == SDLK_UP);
                if (event.key.keysym.sym == SDLK_DOWN);
                if (event.key.keysym.sym == SDLK_LEFT){
                    speedx = 0;
                    accelx = 0;
                    break;
                }
                if (event.key.keysym.sym == SDLK_RIGHT){
                    speedx = 0;
                    accelx = 0;
                    break;
                }
                if (event.key.keysym.sym == SDLK_x);
                if (event.key.keysym.sym == SDLK_c);
                break;

            }
            } // end switch
        } // end of message processing
        if(-maxSpeed<speedx || speedx<maxSpeed){
            speedx += accelAmount*accelx*(1.0/30.0);
        }
        if((speedy>-initialJumpSpeed)&&(player.getState()==JUMPING)){
            if(player.sceneCollision()&&speedy<0){
                player.changeDstRect((float)0, -speedy, &stage);
                speedy = 0;
                accely = 0;
                player.setState(STANDING);
                continue;
            }
            speedy += gravity*accely*(1.0/30.0);
        }

            if(player.getState()==JUMPING){
                player.jump();
            }else {
                    if(speedx==0)
                        player.stand();
                    else
                        player.walk();
            }

        if(speedx>0)
            flip = SDL_FLIP_NONE;
        if(speedx<0)
            flip = SDL_FLIP_HORIZONTAL;
        player.changeDstRect(speedx, speedy, &stage);

        // DRAWING STARTS HERE

        // clear screen
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, bgTex, stage.getSrcrect(), stage.getDstrect());
        SDL_RenderCopyEx(ren, playerTex, player.getSrcRect(), player.getDstRect(), 0.0, NULL, flip);
        SDL_RenderPresent(ren);
        // DRAWING ENDS HERE
        if(1000/FPS > SDL_GetTicks()-fpsCounter){
            SDL_Delay(1000/FPS-(SDL_GetTicks()-fpsCounter));
        }
    } // end main loop

    // free loaded bitmap
    SDL_DestroyTexture(bgTex);
    SDL_DestroyTexture(playerTex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);

    // all is well ;)
    cout << "Exited cleanly" << endl;
    return 0;
}
