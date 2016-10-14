//-optimized surface loading

#include <SDL.h>
#include <cstdio>
#include <string>

#pragma  comment(lib,"SDL2.lib")
#pragma  comment(lib,"SDL2main.lib")

const int WIDTH = 640;
const int HEIGHT = 480;


SDL_Window* gWindow = nullptr;
SDL_Surface* gScreenSurface = nullptr;
SDL_Surface* gStretchedSurface = nullptr;



SDL_Surface* loadSurface(const char* path)
{
    SDL_Surface* pSurface = nullptr;
    SDL_Surface* loadedSurface = SDL_LoadBMP(path);

    if (loadedSurface == nullptr)
    {
        printf("Failed to load Surface%s! Error  %s\n", path,SDL_GetError());
    }
    else
    {
        pSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format,SDL_SWSURFACE);
        if (pSurface == nullptr)
        {
            printf("Unable to optimaize image %s! SDL Error: %s\n", path, SDL_GetError());
        }

        SDL_FreeSurface(loadedSurface);
    }

    return pSurface;
}

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL Coudl not intialize  Error %s \n", SDL_GetError());
        return false;
    }
    else
    {
        gWindow = SDL_CreateWindow("SDL Tutorial 5", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == nullptr)
        {
            printf("Window could not be created ! SDL Error %s ", SDL_GetError());
            return false;
        }
        else
        {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }

    }
    return true;
}

bool loadMedia()
{
    gStretchedSurface = loadSurface("stretch.bmp");
    if (gStretchedSurface == nullptr)
    {
        printf("Failed to load stretch.bmp ");
        return false;
    }
    return true;
}

void close()
{
    SDL_FreeSurface(gStretchedSurface);
    gStretchedSurface = nullptr;

    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

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
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                }

                SDL_Rect  stretchRect = {0,0,WIDTH,HEIGHT};
                SDL_BlitScaled(gStretchedSurface, nullptr, gScreenSurface, &stretchRect);
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }

    close();
    return 0;
}