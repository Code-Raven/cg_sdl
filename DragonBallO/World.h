#pragma once
#include "MyMath.h"

const int NUM_GRID_ROWS = 2;
const int NUM_GRID_COLUMNS = 2;
const int NUM_ZONES = NUM_GRID_ROWS * NUM_GRID_COLUMNS;

using namespace MyMath;

class World
{
public:
	World() {};
	~World() {};
	
	void InitWorldGrid(RectBoundary overlap);
	RectBoundary GetZoneBoundary(int indX, int indY);
	RectBoundary GetZoneBoundary(Float2 worldPos);
	int GetIndX(float posX);
	int GetIndY(float posY);

public:
	RectBoundary worldGrid[NUM_GRID_ROWS][NUM_GRID_COLUMNS];
};

