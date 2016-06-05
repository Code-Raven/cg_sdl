//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

#include "LTexture.h"

class SDLInit{

	public:
		bool Setup();

		bool LoadTexture(LTexture &lTexture);

		void SetColor(LTexture &lTexture, Uint8 red, Uint8 green, Uint8 blue);
		void SetBlendMode(LTexture &lTexture, SDL_BlendMode blending);
		void SetAlpha(LTexture &lTexture, Uint8 alpha);

		void CleanupTexture(LTexture &lTexture);
		bool Cleanup();

		void Render(LTexture &lTexture);
		void Update();
};