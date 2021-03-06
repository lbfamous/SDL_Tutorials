#include "SDL.h"
#include <stdio.h>

#pragma comment(lib,"SDL2.lib")
#pragma comment(lib,"SDL2main.lib")

const int WIDTH = 640;
const int HEIGHT = 480;


SDL_Window* window = nullptr;
SDL_Surface* screenSurface = nullptr;
SDL_Surface* helloWorld = nullptr;


bool init()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stdout, "SDL could not initialzie ! SDL_Error:%s\n", SDL_GetError());
        success = false;
    }
    else
    {
        window = SDL_CreateWindow("Tutorial_3 ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr)
        {
            printf("Window could not be created ! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            screenSurface = SDL_GetWindowSurface(window);
        }
    }
    return success;
}


bool loadMedia()
{
    bool success = true;
    helloWorld = SDL_LoadBMP("helloworld.bmp");
    if (helloWorld == nullptr)
    {
        printf(" unable to load image %s ! SDL_Error: %s\n", "helloworld.bmp", SDL_GetError());
        success = false;
    }
    return success;
}

void close()
{
    SDL_FreeSurface(helloWorld);
    helloWorld = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    SDL_Quit();
}


int main(int argc, char** argv)
{
    

    if (init())
    {
        if (loadMedia())
        {            
            bool quit = false;
            SDL_Event e;

            while (!quit)
            {
                while (SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_QUIT )
                    {
                        quit = true;
                    }

                    if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
                    {
                        quit = true;
                    }
                }
                SDL_BlitSurface(helloWorld, nullptr, screenSurface, nullptr);
                SDL_UpdateWindowSurface(window);
                printf("Tick...\n");
            }
        }
        else
        {
            fprintf(stderr, "failed to load media");
        }
    }
    else
    {
        fprintf(stderr, "Failed init SDL \n");
    }

    close();
    return 0;
}