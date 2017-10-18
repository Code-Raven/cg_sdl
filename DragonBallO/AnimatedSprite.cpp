#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(){}
AnimatedSprite::~AnimatedSprite(){}

void AnimatedSprite::AddAnimIndex(const char* animName, const char* animSeqName, int index) {
	bool animFound = false;

	//Accessing animation...
	for (auto animPair : m_animIndices) {
		if (animPair.first == animName) {
			animFound = true;
			bool seqFound = false;

			//Accessing animation sequence...
			for (auto seqPair : animPair.second) {
				if (seqPair.first == animSeqName) {
					//Adding animation index...
					seqFound = true;
					seqPair.second.push_back(index);
					break;
				}
			}

			if (!seqFound) {
				vector<int> indices = { index };
				pair<const char*, vector<int>> seqPair(animSeqName, indices);
				animPair.second.push_back(seqPair);
			}

			break;
		}
	}

	//If no animation assigned, assign a new animation and sequence...
	if (!animFound) {
		vector<int> indices = { index };
		pair<const char*, vector<int>> seqPair(animSeqName, indices);
		vector < pair<const char*, vector<int>>> seqList = { seqPair };
		pair<const char*, vector<pair<const char*, vector<int>>>> animPair(animName, seqList);
		m_animIndices.push_back(animPair);
	}
}

void SetAnim(const char* animName) {

}

void SetAnimSeq(const char* animSeqName) {

}

void SetAnimClip(int index) {

}

/*
void Player::Attack() {
//Update animation...
if (attackTimer > 0.f) {
attackTimer -= gDeltaTime;	//Updates timer...
float time = 1.f - (attackTimer/attackTime);

int index = (int)(time * ANIM_ATTACK_COUNT) % ANIM_ATTACK_COUNT;
mSpriteClipIndex = animAttackLeftIndices[lastAttackIndex][index];

}	//Start animation...
else if (gFirstKeyDown) {
attackTimer = attackTime;
}
}
*/
