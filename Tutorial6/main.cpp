#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

#pragma  comment(lib,"SDL2.lib")
#pragma  comment(lib,"SDL2main.lib")
#pragma  comment(lib,"SDL2_image.lib")


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


SDL_Window* gWindow = nullptr;
SDL_Surface* gScreenSurface = nullptr;
SDL_Surface* gStretchedSurface = nullptr;
SDL_Surface* gPNGSurface = nullptr;


SDL_Surface* loadSurface(const char* path);


bool init()
{

    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL COULD NOT initialize! SDL Error %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow("SDL Tutotial!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == nullptr)
        {
            printf("Window could not be created ! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags))
            {
                printf("SDL Image could not intialize! SDL_image Error %s\n", IMG_GetError());
                success = false;
            }
            else
            {
                gScreenSurface = SDL_GetWindowSurface(gWindow);
            }
        }
    }
    return success;
}

bool loadMedia()
{
    bool success = true;
    gPNGSurface = loadSurface("loaded.png");
    if (gPNGSurface == nullptr)
    {
        printf("Failed to load PNG image !\n");
        success = false;
    }
    return success;
}

void close()
{
    SDL_FreeSurface(gPNGSurface);
    gPNGSurface = nullptr;

    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    IMG_Quit();
    SDL_Quit();
}


SDL_Surface* loadSurface(const char* path)
{
    SDL_Surface* optimizedSurface = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path);

    if (loadedSurface == nullptr)
    {
        printf("Unable to load image %s! SDL_image Error %s\n", path, IMG_GetError());
    }
    else
    {
        optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, NULL);
        if (optimizedSurface == nullptr)
        {
            printf("Unable to optimaize image %s! SDL_Error: %s\n", path, SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }
    return optimizedSurface;
}


int main(int argc, char** argv)
{
    if (!init())
    {
        printf("Faield to initialzie! \n");
    }
    else
    {
        if (!loadMedia())
        {
            printf("Failed to load media !\n");
        }
        else
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
                SDL_BlitSurface(gPNGSurface, nullptr, gScreenSurface, nullptr);
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }

    close();
    return 0;
}