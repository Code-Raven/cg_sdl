#pragma once
#include <string>
#include <SDL_image.h>
#include "MyMath.h"

class Entity {

friend class SDLInit;
using UInt = unsigned int;
using Int2 = MyMath::Int2;
using Float2 = MyMath::Float2;

public:
	//Needs to be virtual so that derived destructor gets called...
	virtual ~Entity() {};

public:
	void SetPosition(float x, float y);
	void SetMoveSpeed(float moveSpeed);

	void SetCollision(bool blocking) { mCollisionBlocks = blocking; }
	bool CheckCollision(Entity &other);

	MyMath::Float2 GetPosition();

protected:
	Float2 mPos;
	Int2 mSize;

	//If this entity can move, it needs a move speed...
	float mMoveSpeed{ 140.f };

	//For pushing back entity (if collision succeeds)
	bool mCollisionBlocks{false};
};