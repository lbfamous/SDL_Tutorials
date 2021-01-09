#include "Texture.h"
#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>


#define DEFAULT_WIDTH  640
#define DEFAULT_HEIGHT 480

SDL_Renderer* Texture::m_spRender = nullptr;


Texture::Texture():
	m_pTexture(nullptr)
{
	mWidth  = DEFAULT_WIDTH;
	mHeight = DEFAULT_HEIGHT;

}

Texture::Texture(const char* filePath)
{

}

Texture::~Texture()
{

}

bool Texture::loadFromFile(const char* filePath)
{
	free();

	SDL_Texture* newTexture = nullptr;
	SDL_Surface* loadSurface = IMG_Load(filePath);

	if(loadSurface == nullptr){	
		printf("Unable load Image %s!,SDL_Image Error: %s\n",filePath,IMG_GetError());
	}
	else {
		SDL_SetColorKey(loadSurface, SDL_TRUE, SDL_MapRGB(loadSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(m_spRender, loadSurface);
		if (newTexture == nullptr) {
			printf("Unable to create texture from %s! Error %s!\n", filePath, SDL_GetError());
		}
		else {
			mWidth = loadSurface->w;
			mHeight = loadSurface->h;
		}
		SDL_FreeSurface(loadSurface);
	}

	this->m_pTexture = newTexture;
	return m_pTexture != nullptr;
	//return true;
}

void Texture::free()
{
	if (m_pTexture != nullptr) {
		SDL_DestroyTexture(m_pTexture);
		m_pTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
	}
	
}

void Texture::setColor(uint8_t red, uint8_t green, uint8_t blue)
{
	SDL_SetTextureColorMod(m_pTexture, red, green, blue);
}

void Texture::render(int x, int y, SDL_Rect* clip /*= nullptr*/)
{
	SDL_Rect rendQuad = { x,y,mWidth,mHeight };

	if (clip != nullptr) {
		rendQuad.w = clip->w;
		rendQuad.h = clip->h;
	}
	SDL_RenderCopy(this->m_spRender, m_pTexture, clip, &rendQuad);
}

void Texture::render(Point& pt, Color& dwColor, SDL_Rect* clip /*= nullptr*/)
{
	//int x, y = pt.x, pt.y;
	int x = pt.x;
	int y = pt.y;

	SDL_Rect rendQuad = { x,y,mWidth,mHeight };

	if (clip != nullptr) {
		rendQuad.w = clip->w;
		rendQuad.h = clip->h;
	}
	SDL_RenderCopy(this->m_spRender, m_pTexture, clip, &rendQuad);
}

void Texture::destroy()
{
	free();
}

