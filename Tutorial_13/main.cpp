#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string>


#pragma comment(lib,"SDL2.lib")
#pragma comment(lib,"SDL2main.lib")
#pragma comment(lib,"SDL2_image.lib")

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = nullptr;

SDL_Renderer* renderer = nullptr;

class LTexture {
public:
	LTexture() {
		mTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
	}
	~LTexture() {
		free();
	}

public:

	bool loadFromFile(std::string filepath) {
		free();
		SDL_Texture* newTexture = nullptr;
		SDL_Surface* loadedSurface = IMG_Load(filepath.c_str());
		if (loadedSurface == nullptr) {
			printf("Unable to load image %s,SDL_image Error %s\n", filepath.c_str(), IMG_GetError());
		}
		else {
			SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
			newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
			if (newTexture == nullptr) {
				printf("unable to create textaure from %s! SDL Error: %s\n", filepath.c_str(), SDL_GetError());
			}
			else {
				mWidth = loadedSurface->w;
				mHeight = loadedSurface->h;
			}
			SDL_FreeSurface(loadedSurface);
		}

		mTexture = newTexture;
		return(mTexture != nullptr);
	}

	void free() {

		if (mTexture == nullptr) {
			SDL_DestroyTexture(mTexture);
			mTexture = nullptr;
			mWidth = 0;
			mHeight = 0;
		}
	}

	void setColor(Uint8 red,Uint8 green,Uint8 blue) {
		if (mTexture != nullptr) {
			SDL_SetTextureColorMod(mTexture, red, green, blue);
		}
	}

	void setBlendMode(SDL_BlendMode blending) {
		if (mTexture != nullptr) {
			SDL_SetTextureBlendMode(mTexture, blending);
		}
	}

	void setAlpha(Uint8 alpha) {
		if (mTexture != nullptr) {
			SDL_SetTextureAlphaMod(mTexture, alpha);
		}
	}

	void render(int x, int y, SDL_Rect* clip = nullptr) {

		SDL_Rect renderQuad = { x,y,mWidth,mHeight };
		if (clip != nullptr) {
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}
		SDL_RenderCopy(renderer, mTexture, clip, &renderQuad);
	}

	int getWidth() { return mWidth; }

	int getHeight() { return mHeight; }

private:

	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
};

LTexture modulatedTexture;
LTexture backgroundTexture;

bool init() {

	bool successs = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL Could not initialiZe ! SDL Error %s\n", SDL_GetError());
		successs = false;
	}
	else {
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: linear texture filtering not enabled");
		}
		window = SDL_CreateWindow("SDL TUTORIAL 13", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(window == nullptr){
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			successs = false;
		}
		else {
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == nullptr) {
				//
				printf("render error %s\n", SDL_GetError());
				successs = false;
				
			}
			else {
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				int imgFlags = IMG_INIT_PNG;
				if(!(IMG_Init(imgFlags) & imgFlags)){
					successs = false;
				}
			}
		}
	}
	return successs;
}

bool loadMedia() {

	//bool success = true;
	if (modulatedTexture.loadFromFile("../res/fadeout.png")) {
		modulatedTexture.setBlendMode(SDL_BLENDMODE_BLEND);
	}
	else {
		return false;
	}

	if (backgroundTexture.loadFromFile("../res/fadein.png")) {
		return true;
	}

	return false;
}

void close() {

	modulatedTexture.free();
	backgroundTexture.free();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	renderer = nullptr;
	window = nullptr;

	IMG_Quit();
	SDL_Quit();
}





int main(int argc, char** argv) {

	init();
	loadMedia();

	bool quit = false;

	SDL_Event e;
	Uint8 a = 255;
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_w) {
					if (a + 32 > 255) {
						a = 255;
					}
					else {
						a += 32;
					}
				}
				else if (e.key.keysym.sym == SDLK_s) {
					if (a - 32 < 0) {
						a = 0;
					}
					else {
						a -= 32;
					}
				}
			}

		}

		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		backgroundTexture.render(0, 0);
		modulatedTexture.setAlpha(a);
		modulatedTexture.render(0, 0);
		SDL_RenderPresent(renderer);
	}

	close();

	return 0;
}