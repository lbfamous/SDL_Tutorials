#include "SDL.h"
#include <stdio.h>
#include <string>


#pragma comment(lib,"SDL2.lib")
#pragma comment(lib,"SDL2main.lib")

const int WINDTH = 640;
const int HEIGHT = 480;

enum KeyPressSurfaces
{

	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL,
};

bool init();

bool loadMedia();

void close();

SDL_Surface* loadSurface(const std::string& path);


SDL_Window* gWindow = nullptr;
SDL_Surface* gScreenSurface = nullptr;
SDL_Surface* gKeyPressSurface[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* gCurrentSurface = nullptr;


bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL Could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDTH, HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == nullptr)
		{
			printf("Could not be created ! SDL_Error %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return success;
}

bool loadMedia()
{
	bool success = true;
	gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("press.bmp");
	if (gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT] == nullptr)
	{
		printf("Failed to load default image! \n");
		success = false;
	}

	gKeyPressSurface[KEY_PRESS_SURFACE_UP] = loadSurface("up.bmp");
	if (gKeyPressSurface[KEY_PRESS_SURFACE_UP] == nullptr)
	{
		printf("Failed to load UP image! \n");
		success = false;
	}

	gKeyPressSurface[KEY_PRESS_SURFACE_DOWN] = loadSurface("down.bmp");
	if (gKeyPressSurface[KEY_PRESS_SURFACE_DOWN] == nullptr)
	{
		printf("Failed to load DOWN image! \n");
		success = false;
	}

	gKeyPressSurface[KEY_PRESS_SURFACE_LEFT] = loadSurface("left.bmp");
	if (gKeyPressSurface[KEY_PRESS_SURFACE_LEFT] == nullptr)
	{
		printf("Failed to load LEFT image! \n");
		success = false;
	}

	gKeyPressSurface[KEY_PRESS_SURFACE_RIGHT] = loadSurface("right.bmp");
	if (gKeyPressSurface[KEY_PRESS_SURFACE_RIGHT] == nullptr)
	{
		printf("Failed to load RIGHT image! \n");
		success = false;
	}

	return success;
}

void close()
{
	for (int i = 0;i < KEY_PRESS_SURFACE_TOTAL; ++i)
	{
		SDL_FreeSurface(gKeyPressSurface[i]);
		gKeyPressSurface[i] = nullptr;
	}

	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	SDL_Quit();
}

SDL_Surface* loadSurface(const std::string& path)
{
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == nullptr)
	{
		printf("unable to load images %s SDL_Error : %s\n", path.c_str(), SDL_GetError());
	}

	return loadedSurface;
}

int main(int argc,char** argv)
{
	if (!init())
	{
		printf("Failed to initialize \n");
	}
	else
	{
		if (!loadMedia())
		{
			printf("Failed to load media");
		}
		else
		{
			bool quit = false;
			SDL_Event e;
			gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT];

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					else if (e.type == SDL_KEYDOWN)
					{
						switch (e.key.keysym.sym)
						{
						case SDLK_UP:
							gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_UP];
							break;
						case SDLK_DOWN:
							gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_DOWN];
							break;
						case SDLK_LEFT:
							gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_LEFT];
							break;
						case SDLK_RIGHT:
							gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_RIGHT];
							break;
						default:
							gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT];
						}
					}
				}

				SDL_BlitSurface(gCurrentSurface, nullptr, gScreenSurface, nullptr);
				SDL_UpdateWindowSurface(gWindow);
			}

		}
	}
	close();
	return 0;
}



