#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include <string>
#include <cmath>

#pragma comment(lib,"SDL2.lib")
#pragma comment(lib,"SDL2main.lib")
#pragma comment(lib,"SDL2_image.lib")

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();

bool loadMedia();

void close();

SDL_Texture* loadTexture(const std::string& path);

SDL_Window* gWindow = NULL;

SDL_Renderer* gRender = nullptr;

SDL_Texture* gTexture = NULL;

bool init() {

	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {

		printf("SDL Could not initialize! SDL ERROR:%s\n", SDL_GetError());
		success = false;
	}
	else {
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1"))
		{
			printf("Warning: linear texture filter not enabled");
		}

		gWindow = SDL_CreateWindow("SDL_Tutorial9", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			gRender = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRender == NULL) {
				printf("Renderer could not be created! SDL_ERROR: %s",SDL_GetError());
				success = false;
			}
			else {
				SDL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) &imgFlags)) {
					printf("SDL IMAGE could not initialize! SDL_image Error %s\n", IMG_GetError());
					success = false;
				}

			}
		}
	}
	return success;
}


bool loadMedia() {

	bool success = true;

	gTexture = loadTexture("viewport.png");
	if (gTexture == nullptr) {
		printf("Failed to load texture image!\n");
		success = false;
	}
	return success;
}

void close()
{
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;

	SDL_DestroyRenderer(gRender);
	SDL_DestroyWindow(gWindow);

	gWindow = NULL;
	gRender = nullptr;

	IMG_Quit();
	SDL_Quit();

}

SDL_Texture* loadTexture(const std::string& path) {

	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_Image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else {
		newTexture = SDL_CreateTextureFromSurface(gRender, loadedSurface);
		if (newTexture) {
			printf("Unable to create texture from %s! SDL Error:%s\n", path.c_str(), SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}


int main(int argc, char** argv){

	if (!init()) {
		printf("Failed to initialzie! \n");
	}
	else
	{
		if (!loadMedia()) {
			printf("Failed to load media!\n");
		}
		else {
			bool quit = false;

			SDL_Event e;
			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0) {
					if (e.type == SDL_QUIT) {
						quit = true;
					}
				}

				SDL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRender);

				SDL_Rect  topLeftViewport;
				topLeftViewport.x = 0;
				topLeftViewport.y = 0;
				topLeftViewport.w = SCREEN_WIDTH / 2;
				topLeftViewport.h = SCREEN_HEIGHT / 2;
				SDL_RenderSetViewport(gRender, &topLeftViewport);
				SDL_RenderCopy(gRender, gTexture, NULL, NULL);


				SDL_Rect topRightViewport;
				topRightViewport.x = SCREEN_WIDTH / 2;
				topRightViewport.y = 0;
				topRightViewport.w = SCREEN_WIDTH / 2;
				topRightViewport.h = SCREEN_HEIGHT / 2;

				SDL_RenderSetViewport(gRender, &topRightViewport);
				SDL_RenderCopy(gRender, gTexture, NULL, NULL);

				SDL_Rect bottomViewport;
				bottomViewport.x = 0;
				bottomViewport.y = SCREEN_HEIGHT / 2;
				bottomViewport.w = SCREEN_WIDTH;
				bottomViewport.h = SCREEN_HEIGHT / 2;
				SDL_RenderSetViewport(gRender, &bottomViewport);
				SDL_RenderCopy(gRender, gTexture, NULL, NULL);

				SDL_RenderPresent(gRender);
			}
		}
	}

	close();
	return 0;
}