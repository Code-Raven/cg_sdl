#pragma once

#include "Sprite.h"
#include <utility>
#include <vector>

using namespace std;

class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite();
	~AnimatedSprite();

public:
	void AddAnimIndex(const char* animName, const char* animSeqName, int index);

protected:
	vector<pair<const char*, vector<pair<const char*, vector<int>>>>> m_animIndices;
};

