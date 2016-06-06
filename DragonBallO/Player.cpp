#include "Player.h"

#define ANIM_RIGHT_COUNT 2
#define ANIM_LEFT_COUNT 2
#define ANIM_UP_COUNT 2
#define ANIM_DOWN_COUNT 2

extern float gDeltaTime;

extern int gHorizVelocity;
extern int gVertVelocity;

namespace {
	//Animation times...
	float animRightTime = 0.f;
	float animLeftTime = 0.f;
	float animUpTime = 0.f;
	float animDownTime = 0.f;

	//Animation speeds... //TODO: Don't hard code these like this...
	float animSpeed = 12;

	//Animation indices...
	int animRightIndices[ANIM_RIGHT_COUNT] = { 4, 18};
	int animLeftIndices[ANIM_LEFT_COUNT] = { 2, 16 };
	int animUpIndices[ANIM_UP_COUNT] = { 3, 17 };
	int animDownIndices[ANIM_DOWN_COUNT] = { 1, 15 };
}

void Player::Move() {
	//Setting velocity...
	float velocity = mMoveSpeed * gDeltaTime;

	//Update position...
	mXPos += gHorizVelocity * velocity;
	mYPos += gVertVelocity * velocity;

	//Update animation...	//TODO: make this better with animations...
	if (gHorizVelocity > 0) {
		animRightTime += animSpeed * gDeltaTime;

		int index = (int)animRightTime % ANIM_RIGHT_COUNT;
		mSpriteClipIndex = animRightIndices[index];
	}
	else if (gHorizVelocity < 0) {
		animLeftTime += animSpeed * gDeltaTime;

		int index = (int)animLeftTime % ANIM_LEFT_COUNT;
		mSpriteClipIndex = animLeftIndices[index];
	}
	else if (gVertVelocity > 0) {
		animDownTime += animSpeed * gDeltaTime;

		int index = (int)animDownTime % ANIM_DOWN_COUNT;
		mSpriteClipIndex = animDownIndices[index];
	}
	else if (gVertVelocity < 0) {
		animUpTime += animSpeed * gDeltaTime;

		int index = (int)animUpTime % ANIM_UP_COUNT;
		mSpriteClipIndex = animUpIndices[index];
	}
}