#include "Player.h"

extern int gRightAxis;
extern int gLeftAxis;
extern int gUpAxis;
extern int gDownAxis;

void Player::Move() {
	mXPos += gRightAxis + gLeftAxis;
	mYPos += gUpAxis + gDownAxis;
}