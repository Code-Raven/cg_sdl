#pragma once
#include "Sprite.h"
#include "Destructible.h"

class Player : public Sprite, public Destructible {
public:
	//Base class destructor is ALWAYS implicitly called...
	Player() { mCollisionBlocks = false; }
	virtual ~Player() override {}

public:
	void Move();
	void Attack();
};