#include "GameManager.h"
#include "SDLInit.h"
#include "Player.h"
#include "Actor.h"

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

//Screen dimension constants
extern int SCREEN_WIDTH;		//TODO: currently not using...
extern int SCREEN_HEIGHT;		//TODO: currently not using...

static SDLInit sdlInit;

namespace {
	Player player;
}

void InitEntities() {
	//Setting path names...
	player.SetTexturePath("textures/link_sheet.png");

	//Loading textures...
	sdlInit.LoadTexture(player);

	//Setting position information...
	player.SetPosition(0, 0);

	//Setting size information...
	player.SetSize(50, 50);

	//Set sprite sheet information...
	player.InitSpriteSheet(0, 14, 6);
	player.SetSpriteClip(0, 0, 30, 30, 0);
}

bool GameManager::Init(){
	bool initSuccess = sdlInit.Setup();
	if (initSuccess) {
		InitEntities();
	}

	return initSuccess;
}

void GameManager::Cleanup(){
	sdlInit.CleanupTexture(player);
	sdlInit.Cleanup();
}

//TODO: Add deltatime later...
void GameManager::Update() {
	player.Move();
	sdlInit.Update();
}

void GameManager::Render(){
	sdlInit.Render();
	sdlInit.DrawTexture(player);
}