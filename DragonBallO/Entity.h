#pragma once
#include <string>
#include <SDL_image.h>

class Entity{

	friend class SDLInit;

public:
	void SetTexturePath(const char* texturePath);
	void SetPosition(int x, int y);
	void SetSize(int width, int height);

protected:
	//The actual hardware texture
	SDL_Texture* mTexture;
	const char* mTexturePath;

	int mXPos{0}, mYPos{0};
	int mWidth{0}, mHeight{0};
};