#include <stdio.h>
#include <stdlib.h>
//#include "SDL_All.h"  //
#include "ltexture.h"
#include <SDL_Frame.h>

using namespace lf;


const int WALK_ANIMATION_FRAMES = 4;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

LTexture gSpriteSheetTexture;
SDL_Rect gSpriteClip[WALK_ANIMATION_FRAMES];



bool loadMedia() {
	bool success = true;

	if (!gSpriteSheetTexture.loadFromFile(renderer,"../res/foo_2.png")) {
		fprintf(stderr,"Failed to load texture!!!");
		return false;
	}
	gSpriteClip[0].x = 0;
	gSpriteClip[0].y = 0;
	gSpriteClip[0].w = 64;
	gSpriteClip[0].h = 205;

	gSpriteClip[1].x = 64;
	gSpriteClip[1].y = 0;
	gSpriteClip[1].w = 64;
	gSpriteClip[1].h = 205;

	gSpriteClip[2].x = 128;
	gSpriteClip[2].y = 0;
	gSpriteClip[2].w = 64;
	gSpriteClip[2].h = 205;

	gSpriteClip[3].x = 196;
	gSpriteClip[3].y = 0;
	gSpriteClip[3].w = 64;
	gSpriteClip[3].h = 205;

	return true;
}

void close() {
	gSpriteSheetTexture.free();
	destroySDLEnv();
}

void onFrameMove(float delta) {
	fprintf(stdout,"onFrameMove -> %d\n", (int)(1/ delta));

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
	static  int frame = 0;

	SDL_Rect* currentClip = &gSpriteClip[frame / 4];
	gSpriteSheetTexture.render(renderer,(SCREEN_WIDTH - currentClip->w) / 2, (SCREEN_HEIGHT - currentClip->h) / 2, currentClip);
	SDL_RenderPresent(renderer);

	
	++frame;
	if (frame / 4 >= WALK_ANIMATION_FRAMES) {
		frame = 0;
	}
}

int main(int argc, char** argv) {

	bool ret = initSDLEnv(SCREEN_WIDTH,SCREEN_HEIGHT);
	if (!ret) 
		return 1;

	if (!loadMedia()) {
		fprintf(stderr, "Failed to load media!");
	}
	else {		
		SDLEnvMessageQueue(onFrameMove);
	}
	close();
	return 0;
	//也许应该重新设计一下框架  	
}


