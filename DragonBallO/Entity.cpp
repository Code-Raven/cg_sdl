#include "Entity.h"

using namespace MyMath;

void Entity::Update() {
	CheckCollision();
}

void Entity::SetPosition(float x, float y) {
	mPos = { x, y };
}

Float2 Entity::GetPosition() {
	return mPos;
}

void Entity::SetMoveSpeed(float moveSpeed) {
	mMoveSpeed = moveSpeed;
}

void Entity::ConfigureCollision(bool canBePashedBack, Int2 topLeftCollOffset,
	Int2 bottomRightCollOffset) {
	mCanBePushedBack = canBePashedBack;
	mTopLeftCollOffset = topLeftCollOffset;
	mBottomRightCollOffset = bottomRightCollOffset;
}

void Entity::AddCollidableEntity(Entity &entity) {
	mCollidableEntities.push_back(&entity);
}

void Entity::CheckCollision() {
	for (Entity *other : mCollidableEntities) {

		Float2 topLeft = { mPos.x + mTopLeftCollOffset.x ,
			mPos.y + mTopLeftCollOffset.y };
		Float2 topRight = { mPos.x + mSize.x - mBottomRightCollOffset.x,
			mPos.y + mTopLeftCollOffset.y };
		Float2 bottomLeft = { mPos.x + mTopLeftCollOffset.x ,
			mPos.y + mSize.y - mBottomRightCollOffset.y };

		Float2 otherTopLeft = { other->mPos.x + other->mTopLeftCollOffset.x ,
			other->mPos.y + other->mTopLeftCollOffset.y };
		Float2 otherTopRight = { other->mPos.x + other->mSize.x - other->mBottomRightCollOffset.x,
			other->mPos.y + other->mTopLeftCollOffset.y };
		Float2 otherBottomLeft = { other->mPos.x + other->mTopLeftCollOffset.x ,
			other->mPos.y + other->mSize.y - other->mBottomRightCollOffset.y };


		//Checking distances is faster then checking each collision point...
		float collisionWidth = topRight.x - topLeft.x;
		float collisionHeight = bottomLeft.y - topLeft.y;

		float leftDist = otherTopLeft.x - topLeft.x;
		float rightDist = topRight.x - otherTopRight.x;
		bool collidesHoriz = leftDist < collisionWidth && rightDist < collisionWidth;

		float topDist = otherTopLeft.y - topLeft.y;
		float bottomDist = bottomLeft.y - otherBottomLeft.y;
		bool collidesVert = topDist < collisionHeight && bottomDist < collisionHeight;

		bool hasCollided = collidesHoriz && collidesVert;

		if (hasCollided) {
			other->OnCollision(this);
			OnCollision(other);

			if (mCanBePushedBack) {
				if (rightDist > leftDist && rightDist > bottomDist && rightDist > topDist) {
					mPos.x += collisionWidth - rightDist;
				}
				else if (topDist > leftDist && topDist > bottomDist) {
					mPos.y += topDist - collisionHeight;
				}
				else if(leftDist > bottomDist) {
					mPos.x += leftDist - collisionWidth;
				}
				else {
					mPos.y += collisionHeight - bottomDist;
				}
			}
		}
	}
}

void Entity::OnCollision(Entity *other) {
	mHasCollided = true;
}

//bool Entity::CheckCollision(Entity &other) {
//	float leftDist = other.mPos.x - mPos.x;// +mBottomRightCollOffset.x;
//	float upDist = other.mPos.y - mPos.y;// +mBottomRightCollOffset.y;
//	float rightDist = (mPos.x + mSize.x) - (other.mPos.x + other.mSize.x);// -mTopLeftCollOffset.x;
//	float bottDist = (mPos.y + mSize.y) - (other.mPos.y + other.mSize.y);// -mTopLeftCollOffset.y;
//
//	bool collidesHoriz = (rightDist < mSize.x && leftDist < mSize.x);
//	bool collidesVert = (bottDist < mSize.y && upDist < mSize.y);
//	bool hasCollided = collidesHoriz && collidesVert;
//
//	//Handle push back...
//	if (hasCollided && mCollisionBlocks) {
//		//push left...
//		if (leftDist < rightDist && leftDist < upDist && leftDist < bottDist) {
//			other.mPos.x -= mSize.x - rightDist;
//		}	//push right...
//		else if (rightDist < upDist && rightDist < bottDist) {
//			other.mPos.x += mSize.x - leftDist;
//		}	//push up...
//		else if (upDist < bottDist) {
//			other.mPos.y -= mSize.y - bottDist;
//		}	//push down...
//		else {
//			other.mPos.y += mSize.y - upDist;
//		}
//	}
//
//	return hasCollided;
//}