#include "Texture.h"
#include "MyRender.h"
#include "SDL_Env.h"
#include <cstdio>
#include <string>



#pragma comment(lib,"SDL2.lib")
#pragma comment(lib,"SDL2main.lib")
#pragma comment(lib,"SDL2_image.lib")


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* g_pWindow = nullptr;
SDL_Renderer* g_pRenderer = nullptr;
Texture* g_pModulatedTexture = nullptr;

Uint8 r = 0xFF;
Uint8 g = 0xFF;
Uint8 b = 0xFF;


bool init() {

	bool ret = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf(" SDL Could not initialize ! SDL ERROR => %s", SDL_GetError());
		ret = false;
	}
	else {
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")){

			printf("Warning: Linear texture filter not enabled");
		}
		g_pWindow = SDL_CreateWindow("SDL_Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (g_pWindow == nullptr) {
			printf("Window could not be created; %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//SDL_SetRenderDrawColor(glfwWindowShouldClose())
			g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, SDL_RENDERER_ACCELERATED);
			Texture::m_spRender = g_pRenderer;
			SDL_SetRenderDrawColor(g_pRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags)&imgFlags)) {
				printf("SDL_IMAGE FAILED Initialize => %s\n",IMG_GetError());
				ret = false;
			}
		}
	}

	return ret;
}

bool loadMedia() {


	bool ret = true;
	g_pModulatedTexture = new Texture();

	if (!g_pModulatedTexture->loadFromFile("../res/colors.png")) {
		printf("Failed to load colors texture!");
		ret = false;
	}

	return ret;
}

void close() {

	g_pModulatedTexture->destroy();

	SDL_DestroyRenderer(g_pRenderer);
	SDL_DestroyWindow(g_pWindow);

	g_pRenderer = nullptr;
	g_pWindow = nullptr;

	IMG_Quit();
	SDL_Quit();

}


void drawTexture(Texture* texture, Uint8 r, Uint8 g, Uint8 b) {

	texture->setColor(r, g, b);
	texture->render(0, 0);
}





void onRender() {
	fprintf(stderr, "%s\n", __FUNCTION__);

	//Uint8 r = 0xFF;
	//Uint8 g = 0xFF;
	//Uint8 b = 0xFF;


	SDL_SetRenderDrawColor(g_pRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_pRenderer);
	g_pModulatedTexture->setColor(r, g, b);
	g_pModulatedTexture->render(0, 0);
	SDL_RenderPresent(g_pRenderer);
}


void onInputHandler(SDL_Event& e) {

	//fprintf(stderr, "onInputHandler -> %s", __FUNCTION__);

	//Uint8 r = 0xFF;
	//Uint8 g = 0xFF;
	//Uint8 b = 0xFF;

	switch (e.key.keysym.sym) {
		case SDLK_q:
			r += 32;
			break;
		case SDLK_w:
			g += 32;
			break;
		case SDLK_e:
			b += 32;
			break;
		case SDLK_a:
			r -= 32;
			break;
		case SDLK_s:
			g -= 32;
			break;
		case SDLK_d:
			b -= 32;
			break;
	}

}


void msgPump() {
	bool quit = false;
	SDL_Event e;
	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			else {
				onInputHandler(e);
				onRender();
			}
		}
	}
}



class RenderImpl : public Render {

public :

	void onRender() {

	}

	void onInputHandler() {

	}
};

int main(int argc, char** argv) {


	InitSDLEnv();  //-> 初始化环境

	

	
	//SDL_Renderer* render = SDLEnv::GetRenderer();

	auto window = SDLEnv::GetWindow();
	auto render = SDLEnv::GetRenderer();
	//SDL_Renderer* render = SDLEnv::GetRenderer();
	auto texture = new Texture("colors.png");
	
	SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(render);
	if (texture != nullptr) {
				
		Uint8 r = 0xFF;
		Uint8 g = 0xFF;
		Uint8 b = 0xFF;

		texture->render(Point(0, 0), Color(r, g, b));
	}
	SDL_RenderPresent(g_pRenderer);









	if (!init()) {
		printf("%s => Failed to initialzied", __FUNCTION__);
	}
	else {
		if (!loadMedia()) {
			printf("Failed to LoadMedia() ");
		}
		else {

			//bool quit = false;
			//SDL_Event e;

			//uint8_t r = 255;
			//uint8_t g = 255;
			//uint8_t b = 255;

			//while (!quit) {
			//	while (SDL_PollEvent(&e)) {
			//		if (e.type == SDL_QUIT) {
			//			quit = true;
			//		}
			//		else if (e.type == SDL_KEYDOWN) {

			//			switch (e.key.keysym.sym) {

			//			case SDLK_q:
			//				r += 32;
			//				break;
			//			case SDLK_w:
			//				g += 32;
			//				break;
			//			case SDLK_e:
			//				b += 32;
			//				break;
			//			case SDLK_a:
			//				r -= 32;
			//				break;
			//			case SDLK_s:
			//				g -= 32;
			//				break;
			//			case SDLK_d:
			//				b -= 32;
			//				break;
			//			}
			//		}
			//	}
			//	SDL_SetRenderDrawColor(g_pRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			//	SDL_RenderClear(g_pRenderer);
			//	g_pModulatedTexture->setColor(r, g, b);
			//	g_pModulatedTexture->render(0, 0);
			//	SDL_RenderPresent(g_pRenderer);
			//}
			msgPump();
		}
	}

	close();
	return 0;
}



