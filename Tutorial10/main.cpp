//#include <cstdio>
#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include <string>

#pragma comment(lib,"SDL2.lib")
#pragma comment(lib,"SDL2main.lib")
#pragma comment(lib,"SDL2_image.lib")


SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;


class LTexture {

public:
	LTexture() 
	{
		mTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
	}
	~LTexture()
	{
		free();
	}

	bool loadFromFile(const std::string& path) {

		free();
		SDL_Texture* newTexture = nullptr;
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		if (loadedSurface == nullptr) {
			std::string ppath  = std::string("../") + path;
			loadedSurface = IMG_Load(ppath.c_str());
			if(loadedSurface == nullptr) {
				printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
			}
		}

		if (loadedSurface != nullptr){	
			SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
			newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
			if (newTexture == nullptr) {
				printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
			}
			else {
				mWidth = loadedSurface->w;
				mHeight = loadedSurface->h;
			}
			SDL_FreeSurface(loadedSurface);
		}
		mTexture = newTexture;
		return mTexture != nullptr;
	}

	void free() {

		if (mTexture != nullptr)
		{
			SDL_DestroyTexture(mTexture);
			mTexture = nullptr;
			mWidth = 0;
			mHeight = 0;
		}

	}

	void render(int x, int y) {

		SDL_Rect renderQuad = { x,y,mWidth,mHeight };
		SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
	}


	int getWidth() const {
		return mWidth;
	}


	int getHeight() const {
		return mHeight;
	}



private:
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;
};


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;



LTexture gFooTexture;
LTexture gBackgroundTexture;

bool init() {

	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL ERROR: %s\n", SDL_GetError());
		success = false;
	}
	else {

		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1"))
		{
			printf("Warning: Linear texture filter not enabled");
		}

		gWindow = SDL_CreateWindow("SDL_Tutorial 10", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (gWindow == nullptr)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		}
		else {
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL) {
				printf("Renderer could not be created! SDL Error %s\n", SDL_GetError());
				success = false;
			}else {
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags)&imgFlags))
				{
					printf("SDL_IMAGE could not initialize! SDL_image Error %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}

bool loadMedia() {

	bool success = true;
	if (!gFooTexture.loadFromFile("res/foo.png"))
	{
		printf("Failed to load Foo texture image!\n");
		success = false;
	}

	if (!gBackgroundTexture.loadFromFile("res/background.png"))
	{
		printf("Failed to load background texture image!\n");
		success = false;
	}
	return success;
}

void close() {

	gFooTexture.free();
	gBackgroundTexture.free();

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);

	IMG_Quit();
	SDL_Quit();

}

int main(int argc, char** argv)
{

	if (!init()){

		printf("Failed to initialize!\n");
	}
	else {
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else {
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
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF,0xFF);
				SDL_RenderClear(gRenderer);

				gBackgroundTexture.render(0, 0);
				gFooTexture.render(240, 190);

				SDL_RenderPresent(gRenderer);
			}
		}
	}

	close();
	return 0;
}