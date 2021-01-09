#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include <string>

#pragma comment(lib,"SDL2.lib")
#pragma comment(lib,"SDL2main.lib")
#pragma comment(lib,"SDL2_image.lib")


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
SDL_Rect gSpriteClips[4];



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
			std::string ppath = std::string("../") + path;
			loadedSurface = IMG_Load(ppath.c_str());
			if (loadedSurface == nullptr) {
				printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
			}
		}

		if (loadedSurface != nullptr) {
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

	void render(int x, int y,SDL_Rect* clip = nullptr) {

		SDL_Rect renderQuad = { x,y,mWidth,mHeight };

		if (clip != nullptr)
		{
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}
		SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);

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



LTexture gSpriteSheetTexture;

bool init() {

	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0){

		printf("SDL Could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else {

		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1")){
			printf("Warning: Linear texture filtering not enabled!");
		}
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == nullptr)
		{
			printf("Window could not be created! Create Error:%s\n", SDL_GetError());
			success = false;
		}
		else {

			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == nullptr)
			{
				printf("Renderer could not be created! SDL Error %s\n", SDL_GetError());
				success = false;
			}
			else {
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags)&imgFlags))
				{
					printf("SDL image could not initialize! SDL_image Error: %s\n", SDL_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}

bool loadMedia() {

	bool success = true;

	if (!gSpriteSheetTexture.loadFromFile("res/dots.png"))
	{
		printf("Failed to load sprite sheet texture");
		success = false;
	}
	else {

		gSpriteClips[0].x = 0;
		gSpriteClips[0].y = 0;
		gSpriteClips[0].w = 100;
		gSpriteClips[0].h = 100;

		gSpriteClips[1].x = 100;
		gSpriteClips[1].y = 0;
		gSpriteClips[1].w = 100;
		gSpriteClips[1].h = 100;

		gSpriteClips[2].x = 0;
		gSpriteClips[2].y = 100;
		gSpriteClips[2].w = 100;
		gSpriteClips[2].h = 100;

		gSpriteClips[3].x = 100;
		gSpriteClips[3].y = 100;
		gSpriteClips[3].w = 100;
		gSpriteClips[3].h = 100;
	}
	return success;
}

void close() {

	gSpriteSheetTexture.free();

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);

	gWindow = nullptr;
	gRenderer = nullptr;

	IMG_Quit();
	SDL_Quit();


}


int main(int argc, char** argv) {

	if (!init()){
		printf("Failed to initialize!\n");
	}
	else {
	//- 
		if (!loadMedia())
		{

		}
		else {
			bool quit = false;
			SDL_Event e;
			while (!quit) {
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}
			
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				gSpriteSheetTexture.render(0, 0, &gSpriteClips[0]);
				gSpriteSheetTexture.render(SCREEN_WIDTH - gSpriteClips[1].w, 0, &gSpriteClips[1]);
				gSpriteSheetTexture.render(0, SCREEN_HEIGHT - gSpriteClips[2].h, &gSpriteClips[2]);
				gSpriteSheetTexture.render(SCREEN_WIDTH - gSpriteClips[3].w, SCREEN_HEIGHT - gSpriteClips[3].h, &gSpriteClips[0]);
				SDL_RenderPresent(gRenderer);
			}		
	}
}
	


	return 0;
}