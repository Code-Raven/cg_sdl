#include "SDLInit.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

bool SDLInit::Setup(){
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window				//TODO: Make this name global...
		gWindow = SDL_CreateWindow( "Dragon Ball O!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL ) {
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else {
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool SDLInit::LoadTexture(LTexture &lTexture) {
	//This is how we get our file name...
	const char* filePath = lTexture.mTexturePath;

	//The final texture
	SDL_Texture* newTexture = NULL;
	
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(filePath);
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", filePath, IMG_GetError());
	}
	else {
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", filePath, SDL_GetError());
		}
		else {
			//Get image dimensions
			lTexture.mWidth = loadedSurface->w;
			lTexture.mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	lTexture.mTexture = newTexture;
	return newTexture != NULL;
}

void SDLInit::SetColor(LTexture &lTexture, Uint8 red, Uint8 green, Uint8 blue) {
	//Modulate texture rgb
	SDL_SetTextureColorMod(lTexture.mTexture, red, green, blue);
}

void SDLInit::SetBlendMode(LTexture &lTexture, SDL_BlendMode blending) {
	//Set blending function
	SDL_SetTextureBlendMode(lTexture.mTexture, blending);
}

void SDLInit::SetAlpha(LTexture &lTexture, Uint8 alpha) {
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(lTexture.mTexture, alpha);
}

void SDLInit::CleanupTexture(LTexture &lTexture) {
	SDL_DestroyTexture(lTexture.mTexture);
	lTexture.mTexture = NULL;
}

void SDLInit::Render(LTexture &lTexture) {
	////Set rendering space and render to screen
	//SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	////Set clip rendering dimensions
	//if (clip != NULL) {
	//	renderQuad.w = clip->w;
	//	renderQuad.h = clip->h;
	//}

	////Render to screen
	//SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

//TODO: add delta time to update...
void SDLInit::Update(){
	//Update the surface
	SDL_UpdateWindowSurface( gWindow );
	//Wait two seconds
	//SDL_Delay( 2000 );
}

bool SDLInit::Cleanup(){
	bool initSuccess = true;

	//Destroy window
	SDL_DestroyWindow( gWindow );

	//Quit SDL subsystems
	SDL_Quit();

	return initSuccess;
}