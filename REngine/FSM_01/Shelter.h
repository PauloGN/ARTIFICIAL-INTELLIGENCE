#pragma once
#include "AI.h"
#include "REngine.h"

class Shelter : public AI::Entity
{
public:

	Shelter(AI::AIWorld& world);

	void Load(const float X, const float Y);
	void Unload();

	void Update(float deltaTime);
	void Render();
	bool bLightFire;

private:


	Texture2D mTextureShelter;
	Texture2D mTextureFire;

	//Monster animation
	Rectangle mTextureRect;
	int mCurrentFrame = 0;
	float mCurrentTime = 0.0f;
	int mAnimFrames = 5;
	const float mFrameDuration = 0.3f;


	void UpdateAnimation(float deltaTime);

};