#include "Camera.h"

using namespace MyMath;

extern float gDeltaTime;
extern World gWorld;

namespace {
	float panTime = 1.0f;
	int zoneIndX = 0;
	int zoneIndY = 0;
}

void Camera::RestrictTargetToWorld(Entity &target) {
	const auto &zoneBound = gWorld.GetZoneBoundary(zoneIndX, zoneIndY);

	int targetWidth = target.mSize.x - target.mBottomRightCollOffset.x - target.mTopLeftCollOffset.x;
	int targetHeight = target.mSize.y - target.mBottomRightCollOffset.y - target.mTopLeftCollOffset.y;

	RectBoundary targetBound {
		target.mPos.x + target.mTopLeftCollOffset.x,				//left...
		target.mPos.x + target.mTopLeftCollOffset.x + targetWidth,	//right...
		target.mPos.y + target.mTopLeftCollOffset.y,				//top...
		target.mPos.y + target.mTopLeftCollOffset.y + targetHeight,	//bottom...
	};

	//collides left...
	if (targetBound.left < 0.0f) {
		target.mPos.x = -(float)target.mTopLeftCollOffset.x;
		target.mPushbackSides |= 1 << 0;	//can't pushback from right...
	}	//collides right...
	else if (targetBound.right > WORLD_WIDTH) {
		target.mPos.x = float(WORLD_WIDTH - target.mSize.x + target.mBottomRightCollOffset.x);
		target.mPushbackSides |= 1 << 2;	//can't pushback from left...
	}

	//collides top...
	if (targetBound.top < 0.0f) {
		target.mPos.y = -(float)target.mTopLeftCollOffset.y;
		target.mPushbackSides |= 1 << 3;	//can't pushback from bottom...
	}	//collides bottom...
	else if (targetBound.bottom > WORLD_HEIGHT) {
		target.mPos.y = float(WORLD_HEIGHT - target.mSize.y + target.mBottomRightCollOffset.y);
		target.mPushbackSides |= 1 << 1;	//can't pushback from top...
	}
}

void Camera::SetPos(Float2 pos) {
	mPos.x = pos.x - (SCREEN_WIDTH / 2.0f);
	mPos.y = pos.y - (SCREEN_HEIGHT / 2.0f);
}

void Camera::LookAt(Entity &target) {
	mLookAtTarget = &target;

	//Camera follows target...
	if (mMode == Mode::FOLLOW) {
		SetPos({ target.mPos.x + (target.mSize.x / 2.0f), target.mPos.y + (target.mSize.y / 2.0f) });

		//Restricting camera to world coords...
		if (mPos.x < 0.0f) {
			mPos.x = 0.0f;
		}
		if (mPos.y < 0.0f) {
			mPos.y = 0.0f;
		}

		if (mPos.x + SCREEN_WIDTH > WORLD_WIDTH) {
			mPos.x = float(WORLD_WIDTH - SCREEN_WIDTH);
		}
		if (mPos.y + SCREEN_HEIGHT > WORLD_HEIGHT) {
			mPos.y = float(WORLD_HEIGHT - SCREEN_HEIGHT);
		}

		return;
	}

	if (panTime > 1) {
		//else, camera pans over to next screen (when player outside camera bounds...
		int targetWidth = target.mSize.x - target.mBottomRightCollOffset.x - target.mTopLeftCollOffset.x;
		int targetHeight = target.mSize.y - target.mBottomRightCollOffset.y - target.mTopLeftCollOffset.y;

		float nextRight = float((SCREEN_WIDTH + (SCREEN_WIDTH * zoneIndX) -
			(targetWidth * zoneIndX)));
		float nextDown = float((SCREEN_HEIGHT + (SCREEN_HEIGHT * zoneIndY) -
			(target.mBottomRightCollOffset.y * zoneIndY)));
		float nextLeft = float((SCREEN_WIDTH * zoneIndX) -
			(target.mTopLeftCollOffset.x * zoneIndX));

		bool panRight = target.mPos.x + targetWidth > nextRight;
		bool panDown = target.mPos.y + targetHeight + target.mBottomRightCollOffset.y > nextDown;
		//bool panLeft = target.mPos.x + target.mTopLeftCollOffset.x < nextLeft;

		if (panRight) {
			mStartPanPos = mEndPanPos = mPos;
			mEndPanPos.x = nextRight - targetWidth;
			++zoneIndX;
			panTime = 0.0f;
			printf("Pan Right...!\n");
		}
		//else if (panLeft) {
		//	mStartPanPos = mEndPanPos = mPos;
		//	mEndPanPos.x = nextLeft + targetWidth;
		//	--horizScrnIndex;
		//	panTime = 0.0f;
		//	printf("Pan Left...!\n");
		//}

		if (panDown) {
			mStartPanPos = mEndPanPos = mPos;
			mEndPanPos.y = nextDown - targetHeight;
			++zoneIndY;
			panTime = 0.0f;
			printf("Pan Down...!\n");
		}
	}

	panTime += gDeltaTime;
	mPos.x = Lerp(mStartPanPos.x, mEndPanPos.x, panTime);
	mPos.y = Lerp(mStartPanPos.y, mEndPanPos.y, panTime);
}

bool Camera::IsPanning() {
	return panTime < 1.0f;
}
