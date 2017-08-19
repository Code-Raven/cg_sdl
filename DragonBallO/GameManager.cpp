#include "GameManager.h"
#include "SDLInit.h"
#include "Player.h"
#include "Camera.h"

#define SHOW_COLLIDERS false

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

static SDLInit sdlInit;

namespace {
	Camera camera;
	Player player;
	Sprite tree;
	Sprite tree2;
}

void InitEntities() {
	//Setting path names...
	player.SetTexturePath("textures/link_sheet.png");
	tree.SetTexturePath("textures/tree_green.gif");
	tree2.SetTexturePath("textures/tree_green.gif");

	//Loading textures...
	sdlInit.LoadTexture(player);
	sdlInit.LoadTexture(tree);
	sdlInit.LoadTexture(tree2);

	//Setting position information...
	player.SetPosition(0, 0);
	tree.SetPosition(200, 300);
	tree2.SetPosition(200, 150);

	//Setting size information...
	player.SetSpriteSize(50, 50);
	tree.SetSpriteSize(64, 78);
	tree2.SetSpriteSize(64, 78);

	//Set sprite sheet texture coordinates...
	player.InitSpriteSheet(0, 14, 6);
	player.SetSpriteClip(90, 1, 30, 30, 3);			//up...
	player.SetSpriteClip(90, 31, 30, 30, 17);		//up move...
	player.SetSpriteClip(30, 1, 30, 30, 1);			//down...
	player.SetSpriteClip(30, 31, 30, 30, 15);		//down move...
	player.SetSpriteClip(120, 1, 30, 30, 4);		//right...
	player.SetSpriteClip(120, 31, 30, 30, 18);		//right move...
	player.SetSpriteClip(60, 1, 30, 30, 2);			//left...
	player.SetSpriteClip(60, 31, 30, 30, 16);		//left move...

	player.SetSpriteClip(170, 141, 30, 31, 61);		//first left attack...
	player.SetSpriteClip(173, 109, 30, 30, 48);		//second left attack...
	player.SetSpriteClip(173, 71, 30, 30, 34);		//last left attack...

	player.SetSpriteClip(203, 142, 30, 30, 62);		//last right attack...
	player.SetSpriteClip(203, 109, 30, 30, 49);		//second right attack...
	player.SetSpriteClip(203, 77, 30, 31, 35);		//first right attack...

	//Set sprite sheet anchor positions...
	player.SetAnchorOffset({-16, -13}, 61);			//first left attack...
	player.SetAnchorOffset({-23, -10}, 48);			//second left attack...
	player.SetAnchorOffset({-26, -5}, 34);			//last left attack...

	player.SetAnchorOffset({4, 0}, 62);				//last right attack...
	player.SetAnchorOffset({2, -10}, 49);			//second right attack...
	player.SetAnchorOffset({-11, -13}, 35);			//first right attack...=>2

	//Setup collision...
	player.ConfigureCollision(true, { 0, 8 }, { 25, 10 });
	tree.ConfigureCollision(false, { 0, 22 });
	tree2.ConfigureCollision(false, { 0, 22 });

	player.AddCollidableEntity(tree);
	player.AddCollidableEntity(tree2);
}

bool GameManager::Init(){
	bool initSuccess = sdlInit.Setup();
	if (initSuccess) {
		InitEntities();
	}

	return initSuccess;
}

void GameManager::Cleanup(){
	sdlInit.CleanupSprite(player);
	sdlInit.CleanupSprite(tree);
	sdlInit.CleanupSprite(tree2);
	sdlInit.Cleanup();
}

//TODO: Add deltatime later...
void GameManager::Update() {
	player.Update();
	tree.Update();
	tree2.Update();

	//Needs to come last...
	sdlInit.Update();
}

void GameManager::Render(){
	sdlInit.Render();

	sdlInit.DrawSprite(player);
	sdlInit.DrawSprite(tree);
	sdlInit.DrawSprite(tree2);

	//Needs to come last...
	if (SHOW_COLLIDERS) {
		sdlInit.DrawEntityCollider(player);
		sdlInit.DrawEntityCollider(tree);
		sdlInit.DrawEntityCollider(tree2);
	}
}