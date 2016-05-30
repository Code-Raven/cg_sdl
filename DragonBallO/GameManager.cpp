#include "GameManager.h"
#include "SDLInit.h"

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

//Screen dimension constants
extern int SCREEN_WIDTH;		//TODO: currently not using...
extern int SCREEN_HEIGHT;		//TODO: currently not using...

static SDLInit sdlInit;

bool GameManager::Init(){
	bool initSuccess = sdlInit.Setup();
	return initSuccess;
}

bool GameManager::Cleanup(){
	return sdlInit.Cleanup();
}

void GameManager::Render(){
	sdlInit.Update();
}

//TODO: Add deltatime later...
void GameManager::Update() {
	sdlInit.Update();
}