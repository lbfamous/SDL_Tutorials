#ifndef _SDL_ENV_H
#define _SDL_ENV_H

//- 

#include "SDL.h"

class SDLEnv {

public:
	static  void initEnv() {

	}


	static SDL_Renderer* getDevice() {

		return nullptr;
	}


	static SDL_Renderer* GetRenderer() {

		return nullptr;
	}

	static SDL_Window* GetWindow() {

		return nullptr;
	}

	//SDL_CreateWindow
};

//-Render 类似于 DirextX 中的 Device
inline bool InitSDLEnv() {



	return true;
}


#endif
