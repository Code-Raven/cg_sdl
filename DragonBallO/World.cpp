#include "World.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

//extern const int WORLD_WIDTH;
//extern const int WORLD_HEIGHT;

void World::InitWorldGrid(RectBoundary overlap)
{
	float overlapW = overlap.right - overlap.left;
	float overlapH = overlap.top - overlap.bottom;

	for (int indX = 1; indX < NUM_GRID_COLUMNS; ++indX) {
		RectBoundary &nextScrn = worldGrid[0][indX];
		RectBoundary &prevScrn = worldGrid[0][indX - 1];
		nextScrn.left = prevScrn.right - overlapW;
		nextScrn.right = nextScrn.left + SCREEN_WIDTH;
		nextScrn.top = 0;
		nextScrn.bottom = float(SCREEN_HEIGHT);
	}

	for (int indY = 1; indY < NUM_GRID_ROWS; ++indY) {
		RectBoundary &nextScrn = worldGrid[indY][0];
		RectBoundary &prevScrn = worldGrid[indY - 1][0];
		nextScrn.left = 0;
		nextScrn.right = float(SCREEN_WIDTH);
		nextScrn.top = prevScrn.bottom - overlapH;
		nextScrn.bottom = nextScrn.top + SCREEN_HEIGHT;
	}

	for (int indY = 1; indY < NUM_GRID_ROWS; ++indY) {
		for (int indX = 1; indX < NUM_GRID_COLUMNS; ++indX) {
			RectBoundary &nextScrn = worldGrid[indY][indX];
			RectBoundary &prevScrn = worldGrid[indY - 1][indX - 1];
			nextScrn.left = prevScrn.right - overlapW;
			nextScrn.right = nextScrn.left + SCREEN_WIDTH;
			nextScrn.top = prevScrn.bottom - overlapH;
			nextScrn.bottom = nextScrn.top + SCREEN_HEIGHT;
		}
	}
}

RectBoundary World::GetZoneBoundary(int indX, int indY) {
	return worldGrid[indY][indX];
}

RectBoundary World::GetZoneBoundary(Float2 worldPos) {
	int indX = GetIndX(worldPos.x);
	int indY = GetIndX(worldPos.y);
	return GetZoneBoundary(indX, indY);
}

int World::GetIndX(float posX) {
	int indX = int(posX / SCREEN_WIDTH);
	return indX;
}

int World::GetIndY(float posY) {
	int indY = int(posY / SCREEN_HEIGHT);
	return indY;
}
