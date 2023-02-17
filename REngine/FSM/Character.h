#pragma once
#include<REngine.h>
#include<iostream>
#include <AI.h>

struct SpriteInfo
{

	float mSpritXoffset = 64;
	float mSpritYoffset = 64;

	unsigned short mIdleColumn = 0;
	unsigned short mWalkRightColumn = 0;
	unsigned short mWalkLeftColumn = 0;
	unsigned short mWalkUpColumn = 0;
	unsigned short mWalkDownColumn = 0;
	unsigned short mAttackColumn = 0;
				   
	unsigned short mIdleNumberOfSprites = 0;
	unsigned short mWalkNumberOfsprites = 0;
	unsigned short mAttackNumberOfsprites = 0;

	void SetSpriteInfo(float spritXoffset, float spritYoffset, unsigned short IdleColumn, unsigned short WalkRightColumn, unsigned short WalkLeftColumn, unsigned short WalkUpColumn, unsigned short WalkDownColumn, unsigned short AttackColumn, unsigned short IdleNumberOfSprites, unsigned short WalkNumberOfsprites, unsigned short AttackNumberOfsprites)
	{
		mSpritXoffset = spritXoffset;
		mSpritYoffset = spritYoffset;

		mIdleColumn   = IdleColumn;
		mWalkRightColumn = WalkRightColumn;
		mWalkLeftColumn = WalkLeftColumn;
		mWalkUpColumn = WalkUpColumn;
		mWalkDownColumn = WalkDownColumn;
		mAttackColumn = AttackColumn;

		mIdleNumberOfSprites = IdleNumberOfSprites;
		mWalkNumberOfsprites = WalkNumberOfsprites;
		mAttackNumberOfsprites = AttackNumberOfsprites;
	}

};


class Character
{

public:

	//Singleton Functions
	static void StaticInitialize();
	static void StaticTerminate();
	static Character& Get();

	Character();

	void Load(const char* spriteName, const float initialSpeed, float spritXoffset, float spritYoffset, unsigned short IdleColumn, unsigned short WalkRightColumn, unsigned short WalkLeftColumn, unsigned short WalkUpColumn, unsigned short WalkDownColumn, unsigned short AttackColumn, unsigned short IdleNumberOfSprites, unsigned short WalkNumberOfsprites, unsigned short AttackNumberOfsprites);
	
	void Unload();
	void Update(float deltaTime);
	void Render();

	
	const REng::Math::Vector2 GetPlayerPos() const { return mPlayerPos;}

private:

	//Sprites
	Rectangle mRecSprite;
	Texture2D mCharTexture;
	SpriteInfo mSpriteInfo;


	float mMoveSpeed = 0.0f;
	REng::Math::Vector2 mPlayerPos;

	//Animation
	bool bIsMoving;
	float mAnimCurrentTime;
	int mCurrentSprite;

private:

	void PlayerMovement(float deltaTime);
	void Idle(float deltaTime);
	void UpdateRecSprite(bool isMoving, const float recX, const float recY);

};
