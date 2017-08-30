#include "GameManager.h"
#include "SDLInit.h"
#include "Player.h"
#include "Camera.h"

#define CAMERA_MODE Camera::Mode::PAN
#define SHOW_COLLIDERS true

//Also camera dimension...
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int WORLD_WIDTH = 1280;
const int WORLD_HEIGHT = 960;//960;

const int NUM_GRID_ROWS = WORLD_HEIGHT/SCREEN_HEIGHT;
const int NUM_GRID_COLUMNS = WORLD_WIDTH/SCREEN_WIDTH;

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

Camera gCamera(CAMERA_MODE);

static SDLInit sdlInit;

namespace {
	Player player;
	Sprite tree;
	Sprite boulder;

	using RectBoundary = MyMath::RectBoundary;
	RectBoundary worldGrid[NUM_GRID_ROWS][NUM_GRID_COLUMNS];

	//TODO: Create world map...
	void InitWorldGrid(RectBoundary overlap) {
		float overlapW = overlap.right - overlap.left;
		float overlapH = overlap.top - overlap.bottom;

		for (int rowIndx = 0; rowIndx < NUM_GRID_ROWS; ++rowIndx) {
			for (int colIndx = 0; colIndx < NUM_GRID_COLUMNS; ++colIndx) {
				RectBoundary &nextScrn = worldGrid[rowIndx][colIndx];
				/*RectBoundary &prevScrn = (rowIndx - 1 < 0 || colIndx - 1 < 0) ?
					nextScrn : worldGrid[rowIndx - 1][colIndx - 1];*/

				if (rowIndx == 0) {
					nextScrn.left = 0;
					nextScrn.right = SCREEN_WIDTH;
				}
				if (colIndx == 0) {
					nextScrn.top = 0;
					nextScrn.bottom = SCREEN_HEIGHT;
				}



				//rowIndx at 0
				nextScrn.left = 0;
				nextScrn.right = SCREEN_WIDTH;
				nextScrn.top = 0;
				nextScrn.bottom = SCREEN_HEIGHT;

				//rowIndx at 1
				nextScrn.left = prevScrn.right - overlapW;
				nextScrn.right = nextScrn.left + SCREEN_WIDTH;
				nextScrn.top = 0;
				nextScrn.bottom = SCREEN_HEIGHT;
			}
		}
	}
}

void InitEntities() {
	//Setting path names...
	player.SetTexturePath("textures/link_sheet.png");
	tree.SetTexturePath("textures/tree_green.gif");
	boulder.SetTexturePath("textures/boulder.png");

	//Loading textures...
	sdlInit.LoadTexture(player);
	sdlInit.LoadTexture(tree);
	sdlInit.LoadTexture(boulder);

	//Setting position information...
	player.SetPosition(0, 0);
	tree.SetPosition(200, 300);
	boulder.SetPosition(200, 150);

	//Setting size information...
	player.SetSpriteSize(70, 70);
	tree.SetSpriteSize(64, 78);
	boulder.SetSpriteSize(45, 45);

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
	player.ConfigureCollision(true, { 5, 14 }, { 35, 16 });
	tree.ConfigureCollision(false);
	boulder.ConfigureCollision(true);

	player.AddCollidableEntity(tree);
	player.AddCollidableEntity(boulder);
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
	sdlInit.CleanupSprite(boulder);
	sdlInit.Cleanup();
}

//TODO: Add deltatime later...
void GameManager::Update() {
	tree.Update();
	boulder.Update();
	player.Update();

	//Needs to come last...
	gCamera.LookAt(player);

	//gCamera.RestrictTargetToWorld(player);

	sdlInit.Update();
}

void GameManager::Render(){
	sdlInit.Render();

	sdlInit.DrawSprite(tree);
	sdlInit.DrawSprite(boulder);
	sdlInit.DrawSprite(player);

	//Needs to come last...
	if (SHOW_COLLIDERS) {
		sdlInit.DrawEntityCollider(tree);
		sdlInit.DrawEntityCollider(boulder);
		sdlInit.DrawEntityCollider(player);
	}
}