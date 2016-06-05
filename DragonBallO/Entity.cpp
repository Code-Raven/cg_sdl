#include "Entity.h"

void Entity::SetTexturePath(const char* texturePath) {
	mTexturePath = texturePath;
}

void Entity::SetPosition(int x, int y) {
	mXPos = x;
	mYPos = y;
}

void Entity::SetSize(int width, int height) {
	mWidth = width;
	mHeight = height;
}