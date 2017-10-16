#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "bg.h"
#include "kirby.h"
#include "enemy.h"

using namespace std;

enemy enemies[20];
void getEnemies(bg* stage){
     switch(stage->getCurrentStage()){
       case 1:     if((stage->getSrcRectX()+160>=273 && stage->getSrcRectX()+160<=283 && enemies[0].getType()==0)||(stage->getSrcRectX()>=289 && stage->getSrcRectX()<=299 && enemies[0].getType()==0)){
                        enemies[0].initialize(6, 273.0, 80.0);
                    }
                    if(stage->getSrcRectX()+160>=400 && stage->getSrcRectX()+160<=410 && enemies[1].getType()==0||(stage->getSrcRectX()>=416 && stage->getSrcRectX()<=426 && enemies[0].getType()==0)){
                        enemies[1].initialize(3, 400.0, 40.0);
                    }
                    break;
       default: break;
     }
}

int main(int argc, char *argv[])
{
    for (int i=0;i<20;i++)
        enemies[i].initialize(0,0,0);
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
    SDL_Surface* enemySurf = IMG_Load("sprites/enemies.png"); //SDL_LoadBMP("cb.bmp");
    if (!enemySurf)
    {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        cout << "Unable to load bitmap: " << SDL_GetError() << endl;
        return 1;
    }

    SDL_Texture *enemyTex = SDL_CreateTextureFromSurface(ren, enemySurf);
    SDL_FreeSurface(enemySurf);
    if(!enemyTex)
    {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << endl;
        return 1;
    }

    // centre the bitmap on screen
    SDL_Rect srcrect, dstrect;
    const int FPS = 30;
    const float maxSpeed = 1.6;
    const float accelAmount = 1.8;
    const float initialJumpSpeed = 6.0;
    const float gravity = 6.0;
    Uint32 fpsCounter;
    float speedx = 0;
    float speedy = 0;
    float accelx = 0;
    const float accely = -1;
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
                    if (event.key.keysym.sym == SDLK_UP){
                        speedy = initialJumpSpeed/2.0;
                        player.setState(INFLATED);
                    }
                    if (event.key.keysym.sym == SDLK_DOWN){
                        if(player.getState()==STANDING||player.getState()==WALKING){
                            accelx = 0;
                            speedx = 0;
                            player.setState(CRAWL);
                        }
                        break;
                    }
                    if (event.key.keysym.sym == SDLK_LEFT){
                        if(player.getState()!=CRAWL){
                                accelx = -1;
                        }
                        if(player.getState() == STANDING){
                            player.setState(WALKING);
                        }
                        break;
                    }
                    if (event.key.keysym.sym == SDLK_RIGHT){
                        if(player.getState()!=CRAWL){
                                accelx = 1;
                        }
                        if(player.getState() == STANDING){
                            player.setState(WALKING);
                        }
                        break;
                    }
                    if (event.key.keysym.sym == SDLK_x){
                        if(player.getState()!=JUMPING && player.getState()!=INFLATED)
                        {
                            speedy = initialJumpSpeed;
                            player.setState(JUMPING);
                        }
                    }
                    if (event.key.keysym.sym == SDLK_c){
                        if(player.getState()==INFLATED){
                            player.setState(DEINFLATE);
                        }
                    }
                    break;
                }
            case SDL_KEYUP:
            {
                if (event.key.keysym.sym == SDLK_UP);
                if (event.key.keysym.sym == SDLK_DOWN){
                    if(player.getState()==CRAWL){
                        player.setState(STANDING);
                    }
                }
                if (event.key.keysym.sym == SDLK_LEFT){
                    speedx = 0;
                    accelx = 0;
                    if(player.getState() == WALKING){
                        player.setState(STANDING);
                    }
                    break;
                }
                if (event.key.keysym.sym == SDLK_RIGHT){
                    speedx = 0;
                    accelx = 0;
                    if(player.getState() == WALKING){
                        player.setState(STANDING);
                    }
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
            if(speedx*accelx>maxSpeed)
                speedx = accelx*maxSpeed;
        }

        if(player.getState()!=JUMPING && player.getState()!=INFLATED){
            player.changeDstRect((float)0, -8, &stage);
            cout << stage.checkStageCollision(player.getDstRect()) << player.getDstRect()->y << endl;

            if((stage.checkStageCollision(player.getDstRect()))){
                player.changeDstRect((float)0, 8, &stage);
            }else{
                player.changeDstRect((float)0, 8, &stage);
                speedy=0;
                if(player.getState()!=DEINFLATE){
                    player.setState(JUMPING);
                }
            }
        }

        if((player.getState()==JUMPING)){
            //7cout << stage.checkStageCollision(player.getDstRect()) << endl;
            player.changeDstRect((float)0, speedy, &stage);
            if((stage.checkStageCollision(player.getDstRect()))){
                player.setState(STANDING);
                player.changeDstRect((float)0, -speedy+2, &stage);
                speedy = 0;
            }
            speedy += gravity*accely*(1.0/30.0);
        }
        if((player.getState()==INFLATED)){
            //7cout << stage.checkStageCollision(player.getDstRect()) << endl;
            player.changeDstRect((float)0, speedy, &stage);
            if((stage.checkStageCollision(player.getDstRect()))){
                player.changeDstRect((float)0, -speedy+2, &stage);
                speedy = 0;
            }
            speedy += gravity*accely*(1.0/30.0);
        }

            if(player.getState()==JUMPING){
                player.jump();
            }
            if(player.getState()==INFLATED){
                player.inflate();
            }
            if(player.getState()==DEINFLATE){
                player.deinflate();
            }
            if(player.getState()==STANDING){
                if(speedx!=0){
                    player.setState(WALKING);
                }else{
                    player.stand();
                }
            }
            if(player.getState()==WALKING){
                player.walk();
            }
            if(player.getState()==CRAWL){
                player.crawl();
            }

        if(speedx>0)
            flip = SDL_FLIP_NONE;
        if(speedx<0)
            flip = SDL_FLIP_HORIZONTAL;
        player.changeDstRect(speedx, 0, &stage);
        if(stage.checkStageCollision(player.getDstRect())){
            player.changeDstRect(-speedx,0, &stage);
            cout << stage.checkStageCollision(player.getDstRect()) << endl;
        }
        if(player.getDstRect()->x<=1){
            player.changeDstRect(-speedx,0,&stage);
        }

        getEnemies(&stage);
        for(int i = 0; i<20;i++){
            if((enemies[i].getType()!=0));
                enemies[i].movement(&stage);
        }
        // DRAWING STARTS HERE

        // clear screen
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, bgTex, stage.getSrcrect(), stage.getDstrect());
        SDL_RenderCopyEx(ren, playerTex, player.getSrcRect(), player.getDstRect(), 0.0, NULL, flip);
        for(int i = 0;i<20;i++){
            if(enemies[i].getType()!=0){
                cout << "enemy" << i << endl;
                player.hit(&enemies[i]);
                SDL_RenderCopyEx(ren, enemyTex, enemies[i].getSrcRect(), enemies[i].getDstRect(), 0.0, NULL, enemies[i].getFlip());
                if(enemies[i].getDstRect()->x < -60)
                    enemies[i].initialize(0,0,0);
            }
        }
        player.isHit();
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
