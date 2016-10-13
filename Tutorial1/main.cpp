//#include <iostream>
//INIT SDL_Window

#include "SDL.h"
#include <stdio.h>
#pragma comment(lib,"SDL2.lib")
#pragma comment(lib,"SDL2main.lib")

const int WIDTH = 640;
const int HEIGHT = 480;


int main(int argc,char** argv)
{
    SDL_Window* window = nullptr;
    SDL_Surface* screenSurface = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL Could not initialize! SDL_ERROR: %s\n", SDL_GetError());
    }
    else
    {
        window = SDL_CreateWindow("SDL_Tutorial1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr)
        {
            printf("Window could not be created! SDL_ErrorL: %s\n", SDL_GetError());
        }
        else
        {
            screenSurface = SDL_GetWindowSurface(window);
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
            SDL_UpdateWindowSurface(window);
            SDL_Delay(20000);
            printf("SDL_DESTROYED\n");
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    //system("pause");
    return 0;
}