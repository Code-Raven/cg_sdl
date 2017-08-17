#include "Entity.h"

using Float2 = MyMath::Float2;

void Entity::SetPosition(float x, float y) {
	mPos = { x, y };
}

Float2 Entity::GetPosition() {
	return mPos;
}

void Entity::SetMoveSpeed(float moveSpeed) {
	mMoveSpeed = moveSpeed;
}

bool Entity::CheckCollision(Entity &other) {
	float leftDist = other.mPos.x - mPos.x;
	float upDist = other.mPos.y - mPos.y;
	float rightDist = (mPos.x + mSize.x) - (other.mPos.x + other.mSize.x);
	float downDist = (mPos.y + mSize.y) - (other.mPos.y + other.mSize.y);

	bool collidesHoriz = (rightDist < mSize.x && leftDist < mSize.x);
	bool collidesVert = (downDist < mSize.y && upDist < mSize.y);
	bool hasCollided = collidesHoriz && collidesVert;

	//Handle push back...
	if (hasCollided && mCollisionBlocks) {
		//push left...
		if (leftDist < rightDist && leftDist < upDist && leftDist < downDist) {
			other.mPos.x -= mSize.x - rightDist;
		}	//push right...
		else if (rightDist < upDist && rightDist < downDist) {
			other.mPos.x += mSize.x - leftDist;
		}	//push up...
		else if (upDist < downDist) {
			other.mPos.y -= mSize.y - downDist;
		}	//push down...
		else {
			other.mPos.y += mSize.y - upDist;
		}
	}

	return hasCollided;
}