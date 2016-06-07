#include "Entity.h"

Entity::~Entity() {
	if (mSpriteCLips == nullptr) {
		delete[] mSpriteCLips;
		mSpriteCLips = nullptr;
	}
}

void Entity::SetTexturePath(const char* texturePath) {
	mTexturePath = texturePath;
}

void Entity::SetPosition(float x, float y) {
	mXPos = x;
	mYPos = y;
}

void Entity::SetSize(int width, int height) {
	mWidth = width;
	mHeight = height;
}

void Entity::InitSpriteSheet(uInt startClipIndex, uInt numSpriteCLipsX, uInt numSpriteClipsY) {
	if (numSpriteCLipsX == 0 || numSpriteClipsY == 0) {
		printf("Number of sprite clips must be at least 1.");
		return;
	}

	mNumSpriteClips = numSpriteCLipsX * numSpriteClipsY;
	mNumSpriteClipsX = numSpriteCLipsX;
	mNumSpriteClipsY = numSpriteClipsY;

	mSpriteCLips = new SDL_Rect[mNumSpriteClips];
	mSpriteClipIndex = startClipIndex;
}

void Entity::SetSpriteClip(int x, int y, uInt w, uInt h, uInt index) {
	if (mSpriteCLips == NULL) {
		printf("Cannot set sprite clip. Please call InitSpriteSheet first.");
		return;
	}

	int i = index % mNumSpriteClips;
	mSpriteCLips[i].x = x; mSpriteCLips[i].y = y;
	mSpriteCLips[i].w = w; mSpriteCLips[i].h = h;
}

bool Entity::CheckCollision(Entity &other) {
	float leftDist = other.mXPos - mXPos;
	float upDist = other.mYPos - mYPos;
	float rightDist = (mXPos + mWidth) - (other.mXPos + other.mWidth);
	float downDist = (mYPos + mHeight) - (other.mYPos + other.mHeight);

	bool collidesHoriz = (rightDist < mWidth && leftDist < mWidth);
	bool collidesVert = (downDist < mHeight && upDist < mHeight);
	bool hasCollided = collidesHoriz && collidesVert;

	//Handle push back...
	if (hasCollided && mCollisionBlocks) {
		//push left...
		if (leftDist < rightDist && leftDist < upDist && leftDist < downDist) {
			other.mXPos -= mWidth - rightDist;
		}	//push right...
		else if (rightDist < upDist && rightDist < downDist) {
			other.mXPos += mWidth - leftDist;
		}	//push up...
		else if (upDist < downDist) {
			other.mYPos -= mHeight - downDist;
		}	//push down...
		else {
			other.mYPos += mHeight - upDist;
		}
	}

	return hasCollided;
}

SDL_Rect* Entity::GetSpriteClip() {
	return mSpriteCLips + mSpriteClipIndex;
}