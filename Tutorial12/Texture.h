#ifndef _TEXTURE_H_
#define _TEXTURE_H_


#include <SDL.h>
#include <SDL_image.h>
#include <cstdint>

struct _Point{

	int32_t x;
	int32_t y;

	_Point(int32_t _x, int32_t _y) {
		x = _x;
		y = _y;
	}
};

typedef struct _Point Point;

struct _Color {

	Uint8 r;
	Uint8 g;
	Uint8 b;

	_Color(Uint8 _r, Uint8 _g, Uint8 _b) {
		r = _r;
		g = _g;
		b = _b;
	}
};

typedef struct _Color Color;





class Texture {

public:
	static SDL_Renderer* m_spRender;

public:
	Texture();
	Texture(const char* filePath);

	virtual ~Texture();

public:

	bool loadFromFile(const char* filePath);

	void free();

	void setColor(uint8_t red, uint8_t green, uint8_t blue);

	//-
	void render(int x, int y, SDL_Rect* clip = nullptr);
	//- 渲染位置
	void render(Point& pt, Color& dwColor,SDL_Rect* clip = nullptr);

	int getWidth() const { return mWidth; }
	int getHeight() const { return mHeight; }


	

	//- 销毁函数
	void destroy();
private:

	SDL_Renderer* m_pRender;
	SDL_Texture* m_pTexture;

	int mWidth;
	int mHeight;
};



//-
inline void destroyTexture(Texture* pTexture) {


}
#endif
