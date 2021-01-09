//#include <iostream>
//using namespace std;

//#include "Texture.h"
//#include "MyRender.h"
//#include "SDL_Env.h"
//#include "SDL_Env.h"
#include "SDL.h"
#include <cstdio>
#include <string>


#pragma comment(lib,"SDL2.lib")
#pragma comment(lib,"SDL2main.lib")
#pragma comment(lib,"SDL2_image.lib")


class RenderImpl
{

public:
	void onRender(float delta = 0.f) {

		fprintf(stderr, "%s ==> %f\n", __FUNCTION__, delta);
	}


	void onInputHandler(SDL_Event& e) {
		fprintf(stderr, "%s ==> %d", __FUNCTION__,e.type);

	}
private:

	//uint32_t pos;
	//uint32_t 
};


bool init() {

	return true;
}




int main(int argc, char** argv) {

	//cout << "Hello World" << endl;

	//InitSDLEnv();

	
	RenderImpl* pImpl = new RenderImpl();

	bool quit = false;
	SDL_Event e;
	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			else {
				pImpl->onInputHandler(e);
			}			
		}
		pImpl->onRender();
	}

	delete pImpl;
	pImpl = nullptr;

	return 0;
}