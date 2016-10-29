//Tutorial 7 Texture Loading and Rendering

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#pragma comment(lib,"SDL2.lib")
#pragma comment(lib,"SDL2main.lib")
#pragma comment(lib,"SDL2_image.lib")

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();

bool loadMedia();

void close();

SDL_Texture* loadTexture(const char* path);

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRender = nullptr;
SDL_Texture* gTexture = nullptr;

bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not intialize ! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("WARNING: Linear texture filtering not enabled!");
		}

		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == nullptr)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			gRender = SDL_CreateRenderer(gWindow, 1, SDL_RENDERER_ACCELERATED);
			if (gRender == nullptr)
			{
				printf("Renderer could not be created ! SDL_Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error %s \n", IMG_GetError());
					success = false;
				}
				
			}

		}
	}
	return success;
}

bool loadMedia()
{
	bool success = true;
	gTexture = loadTexture("texture.png");
	if (gTexture == nullptr)
	{
		printf("Failed to load texture image! \n");
		success = false;
	}
	return success;
}

void close()
{
	SDL_DestroyTexture(gTexture);
	gTexture = nullptr;

	SDL_DestroyRenderer(gRender);
	SDL_DestroyWindow(gWindow);

	gWindow = nullptr;
	gRender = nullptr;

	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture(const char* path)
{
	SDL_Texture* newTexture = nullptr;
	SDL_Surface* loadedSurface = IMG_Load(path);

	if (loadedSurface == nullptr)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(gRender, loadedSurface);
		if (newTexture == nullptr)
		{
			printf("Unable to create texture from %s ! SDL Error: %s\n", path, SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}


int main(int argc, char** argv)
{
	if (!init())
	{
		printf("Failed to initialzie! \n");
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
				SDL_RenderClear(gRender);
				SDL_RenderCopy(gRender, gTexture, nullptr, nullptr);
				SDL_RenderPresent(gRender);
			}
		}
	}
	return 0;
}