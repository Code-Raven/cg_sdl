#pragma once
#include "Sprite.h"
#include "Destructible.h"

using namespace std;

class Actor : public Sprite, public Destructible {
public:
	//Base class destructor is ALWAYS implicitly called...
	Actor() { mCanBePushedBack = false; }
	virtual ~Actor() override {}

public:
	void Update() override;

private:
	void Move();
	void Attack();
};