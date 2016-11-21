//Tutorial8 -08-geometry rendering
//渲染图形

#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include <string>
#include <cmath>

#pragma comment(lib,"SDL2.lib")
#pragma comment(lib,"SDL2main.lib")
#pragma comment(lib,"SDL2_image.lib")


const int SCRREN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();

bool loadMedia();

void close();


SDL_Texture* loadTexture(const std::string& path);

SDL_Window* gWindow = nullptr;

SDL_Renderer* gRender = nullptr;

bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL Could not initialize ! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1"))
		{
			printf("Warning: Linear texture filter not enabled");
		}

		gWindow = SDL_CreateWindow("SDL Tutorial8", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCRREN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == nullptr)
		{
			printf("Window could not be crated ! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			gRender = SDL_CreateRenderer(gWindow, 1, SDL_RENDERER_ACCELERATED);
			if (gRender == nullptr)
			{
				printf("Render could not be created ! SDL Error %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!IMG_Init(imgFlags) & imgFlags)
				{
					printf("SDL_image could not be initialized ! SDL_image Error %s\n", IMG_GetError());
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
	return success;
}

void close()
{
	SDL_DestroyRenderer(gRender);
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;
	gRender = NULL;
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture(const std::string& path)
{
	SDL_Texture* newTexture = nullptr;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == nullptr)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(),IMG_GetError());

	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(gRender, loadedSurface);
		if (newTexture == nullptr)
		{
			printf("Unable to crate texture from %s,SDL_Error %s\n", path.c_str(), SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;

}

int main(int argc, char** argv)
{
	if (!init())
	{
		printf("Failed to load media\n");
	}
	else
	{
		if (!loadMedia())
		{
			printf("Failed to load media\n");;
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

				SDL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRender);

				SDL_Rect fillRect = {
					SCRREN_WIDTH / 4,SCREEN_HEIGHT / 4,SCRREN_WIDTH / 2,SCREEN_HEIGHT / 2
				};
				SDL_SetRenderDrawColor(gRender, 0xFF, 0x00, 0x00, 0x00);
				SDL_RenderFillRect(gRender, &fillRect);


				SDL_Rect outlineRect = {
						SCRREN_WIDTH / 6,
						SCREEN_HEIGHT / 6,
						SCRREN_WIDTH * 2 / 3,
						SCREEN_HEIGHT * 2 / 3
				};
				SDL_SetRenderDrawColor(gRender, 0x00, 0xFF, 0x00, 0xFF);
				SDL_RenderDrawRect(gRender, &outlineRect);

				SDL_SetRenderDrawColor(gRender, 0x00, 0x00, 0xFF, 0xFF);
				SDL_RenderDrawLine(gRender, 0, SCREEN_HEIGHT / 2, SCRREN_WIDTH, SCREEN_HEIGHT / 2);
				SDL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0X00, 0XFF);

				for (int i = 0;i < SCREEN_HEIGHT;i += 4)
				{
					SDL_RenderDrawPoint(gRender, SCRREN_WIDTH / 2, i);
				}

				SDL_RenderPresent(gRender);
			}
		}
	}
	close();

	return 0;
}