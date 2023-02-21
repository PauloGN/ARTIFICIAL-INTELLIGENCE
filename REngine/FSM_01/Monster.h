#pragma once
#include "AI.h"
#include "REngine.h"

class Monster: public AI::Entity
{
public:

	Monster(AI::AIWorld& world);
	
	void Load(int index);
	void Unload();

	void Update(float deltaTime);
	void Render();

	bool IsDesfeated() const { return bIsDefeated; }

private:

	bool bIsDefeated;
	Texture2D mTexture;

	//Monster animation
	Rectangle mTextureRect;
	int mCurrentFrame = 0;
	float mCurrentTime = 0.0f;
	int mAnimFrames = 4;
	const float mFrameDuration = 0.3f;

	void UpdateAnimation(float deltaTime);

};
