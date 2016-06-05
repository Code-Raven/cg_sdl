#include "Player.h"

extern int gHorizVelocity;
extern int gVertVelocity;

void Player::Move() {
	mXPos += gHorizVelocity;
	mYPos += gVertVelocity;
}