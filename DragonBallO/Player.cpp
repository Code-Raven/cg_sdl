#include "Player.h"

#define ANIM_RIGHT_COUNT 2
#define ANIM_LEFT_COUNT 2
#define ANIM_UP_COUNT 2
#define ANIM_DOWN_COUNT 2

#define ANIM_ATTACK_COUNT 3

extern float gDeltaTime;

//Keys held down...
extern int gHorizKeysHeld;	//keys a and b
extern int gVertKeysHeld;	//keys w and s

//Keys pressed...
extern bool gFirstKeyDown;	//keys 1
extern bool gSecondKeyDown;	//keys 2
extern bool gThirdKeyDown;	//keys 3
extern bool gFourthKeyDown;	//keys 4

//Keys released...
extern bool gFirstKeyUp;	//keys 2
extern bool gSecondKeyUp;	//keys 2
extern bool gThirdKeyUp;	//keys 3
extern bool gFourthKeyUp;	//keys 4

static int lastAnimIndex = 4;

namespace {
	//Animation times...
	float attackTime = 0.25f;

	//Animation timers...
	float moveRightTimer = 0.f;
	float moveLeftTimer = 0.f;
	float moveUpTimer = 0.f;
	float moveDownTimer = 0.f;

	float attackTimer = 0.0f;

	//Animation speeds...
	float animMoveSpeed = 12;
	float animAttackSpeed = 12;

	//Animation indices...
	int animRightIndices[ANIM_RIGHT_COUNT] = { 4, 18};
	int animLeftIndices[ANIM_LEFT_COUNT] = { 2, 16 };
	int animUpIndices[ANIM_UP_COUNT] = { 3, 17 };
	int animDownIndices[ANIM_DOWN_COUNT] = { 1, 15 };

	int animAttackLeftIndices[ANIM_ATTACK_COUNT] = { 61, 48, 34 };
}

void Player::Move() {
	//If we are attacking we want to stop movement...
	if (attackTimer > 0.f) {
		return;
	}

	//Setting velocity...
	float velocity = mMoveSpeed * gDeltaTime;

	//Update position...	//TODO: Should create velocity vector and normalize...
	mXPos += gHorizKeysHeld * velocity;
	mYPos += gVertKeysHeld * velocity;

	//Update animations...
	if (gHorizKeysHeld > 0) {
		moveRightTimer += animMoveSpeed * gDeltaTime;

		int index = (int)moveRightTimer % ANIM_RIGHT_COUNT;
		mSpriteClipIndex = animRightIndices[index];
		lastAnimIndex = animRightIndices[0];
	}
	else if (gHorizKeysHeld < 0) {
		moveLeftTimer += animMoveSpeed * gDeltaTime;

		int index = (int)moveLeftTimer % ANIM_LEFT_COUNT;
		mSpriteClipIndex = animLeftIndices[index];
		lastAnimIndex = animLeftIndices[0];
	}
	else if (gVertKeysHeld > 0) {
		moveDownTimer += animMoveSpeed * gDeltaTime;

		int index = (int)moveDownTimer % ANIM_DOWN_COUNT;
		mSpriteClipIndex = animDownIndices[index];
		lastAnimIndex = animDownIndices[0];
	}
	else if (gVertKeysHeld < 0) {
		moveUpTimer += animMoveSpeed * gDeltaTime;

		int index = (int)moveUpTimer % ANIM_UP_COUNT;
		mSpriteClipIndex = animUpIndices[index];
		lastAnimIndex = animUpIndices[0];
	}
	else {
		mSpriteClipIndex = lastAnimIndex;
	}
}

void Player::Attack() {
	//Update animation...
	if (attackTimer > 0.f) {
		attackTimer -= gDeltaTime;	//Updates timer...
		float time = 1.f - (attackTimer/attackTime);

		int index = (int)(time * ANIM_ATTACK_COUNT) % ANIM_ATTACK_COUNT;
		mSpriteClipIndex = animAttackLeftIndices[index];

	}	//Start animation...
	else if (gFirstKeyDown) {
		attackTimer = attackTime;
	}
}