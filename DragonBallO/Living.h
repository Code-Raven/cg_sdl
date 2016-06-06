#pragma once
#include "Entity.h"

class Living : public Entity {
public:
	virtual void Move() = 0;

	void SetHealth(int health, int maxHealth);
	void SetMoveSpeed(float moveSpeed);

	bool TakeDamage(int damage);

protected:
	int mMaxHealth{100};
	int mHealth{100};

	float mMoveSpeed{160.f};

	//TODO: add typedef struct for inventory...
	//TODO: struct for weapons to attach and give damage...
};