#include "Character.h"

namespace
{
	//Singleton instance
	std::unique_ptr<Character> charInstance;


	enum class LastMove : int8_t
	{
		LM_Rigth,
		LM_Left,
		LM_Up,
		LM_Down,
		none
	};

	LastMove lastMove = LastMove::none;

}

void Character::StaticInitialize()
{
	assert(charInstance == nullptr, "charInstance already instantiated...\n");
	charInstance = std::make_unique<Character>();
}

void Character::StaticTerminate()
{
	charInstance.reset();
}

Character& Character::Get()
{
	assert(charInstance != nullptr, "charInstance not created yet must call StaticInitialize() first.\n");
	return *charInstance;
}

void Character::Load(const char* spriteName, const float initialSpeed, float spritXoffset, float spritYoffset, unsigned short IdleColumn, unsigned short WalkRightColumn, unsigned short WalkLeftColumn, unsigned short WalkUpColumn, unsigned short WalkDownColumn, unsigned short AttackColumn, unsigned short IdleNumberOfSprites, unsigned short WalkNumberOfsprites, unsigned short AttackNumberOfsprites)
{

	mSpriteInfo.SetSpriteInfo(spritXoffset, spritYoffset, IdleColumn, WalkRightColumn, WalkLeftColumn, WalkUpColumn, WalkDownColumn, AttackColumn, IdleNumberOfSprites, WalkNumberOfsprites, AttackNumberOfsprites);

	//Set Initial Speed
	initialSpeed > 1.f ? mMoveSpeed = initialSpeed : mMoveSpeed = 45.f;

	//Rectangle initial position and size
	const int yInitialSpriteRowNumber = mSpriteInfo.mIdleColumn;//go down till get the Idle initial position
	mRecSprite.x = 0.f;
	mRecSprite.y = yInitialSpriteRowNumber * mSpriteInfo.mSpritYoffset; 
	mRecSprite.width = mSpriteInfo.mSpritXoffset;
	mRecSprite.height = mSpriteInfo.mSpritYoffset;

	//load sprite sheet
	std::string fullPath;
	REng::ResourcesFullPath(spriteName, fullPath);
	mCharTexture = LoadTexture(fullPath.c_str());
	bIsMoving = false;
}

void Character::Unload()
{

	mMoveSpeed = 0.f;
	mCharTexture = Texture2D();
	mPlayerPos = REng::Math::Vector2();
	mRecSprite = Rectangle();
	bIsMoving = false;
	mAnimCurrentTime = 0.f;
	mCurrentSprite = 0;

}

void Character::Update(float deltaTime)
{
	PlayerMovement(deltaTime);
}

void Character::Render()
{
	//DrawTexture(mCharTexture, mPlayerPos.x, mPlayerPos.y, WHITE);
	DrawTextureRec(mCharTexture, mRecSprite, {mPlayerPos.x, mPlayerPos.y}, WHITE);
}
 
Character::Character()
{
	
	mMoveSpeed = 0.f;
	mCharTexture = Texture2D();
	mPlayerPos = REng::Math::Vector2(32.f, 32.f);
	mRecSprite = Rectangle();
	bIsMoving = false;
	mAnimCurrentTime = 0.f;
	mCurrentSprite = 0;
}


void Character::PlayerMovement(float deltaTime)
{


	if (IsKeyDown(KeyboardKey::KEY_RIGHT))
	{
	
		float xRecPos = 0.f;
		const int yRecPos = mSpriteInfo.mSpritYoffset * mSpriteInfo.mWalkRightColumn;
		const int maxNumbersOfSprites = mSpriteInfo.mWalkNumberOfsprites;

		const float animationMaxTime = .2f;

		mAnimCurrentTime += deltaTime;
		if (mAnimCurrentTime >= animationMaxTime)
		{
			xRecPos = mSpriteInfo.mSpritXoffset * mCurrentSprite++;
			UpdateRecSprite(true, xRecPos, yRecPos);
			mAnimCurrentTime = 0.f;
			if (mCurrentSprite >= maxNumbersOfSprites)
			{
				mCurrentSprite = 0;
			}
		}

		mPlayerPos.x += mMoveSpeed * deltaTime;
		lastMove = LastMove::LM_Rigth;
	}


	if (IsKeyDown(KeyboardKey::KEY_LEFT))
	{
		float xRecPos = 0.f;
		const int yRecPos = mSpriteInfo.mSpritYoffset * mSpriteInfo.mWalkLeftColumn;
		const int maxNumbersOfSprites = mSpriteInfo.mWalkNumberOfsprites;

		float animationMaxTime = .2f;

		mAnimCurrentTime += deltaTime;
		if (mAnimCurrentTime >= animationMaxTime)
		{
			xRecPos = mSpriteInfo.mSpritXoffset * mCurrentSprite++;
			UpdateRecSprite(true, xRecPos, yRecPos);
			mAnimCurrentTime = 0.f;
			if (mCurrentSprite >= maxNumbersOfSprites)
			{
				mCurrentSprite = 0;
			}
		}

		mPlayerPos.x -= mMoveSpeed * deltaTime;
		lastMove = LastMove::LM_Left;
	}

	if (IsKeyDown(KeyboardKey::KEY_UP))
	{
		float xRecPos = 0.f;
		const int yRecPos = mSpriteInfo.mSpritYoffset * mSpriteInfo.mWalkUpColumn;
		const int maxNumbersOfSprites = mSpriteInfo.mWalkNumberOfsprites;

		float animationMaxTime = .2f;

		mAnimCurrentTime += deltaTime;
		if (mAnimCurrentTime >= animationMaxTime)
		{
			xRecPos = mSpriteInfo.mSpritXoffset * mCurrentSprite++;
			UpdateRecSprite(true, xRecPos, yRecPos);
			mAnimCurrentTime = 0.f;
			if (mCurrentSprite >= maxNumbersOfSprites)
			{
				mCurrentSprite = 0;
			}
		}

		mPlayerPos.y -= mMoveSpeed * deltaTime;
		lastMove = LastMove::LM_Up;
	}


	if (IsKeyDown(KeyboardKey::KEY_DOWN))
	{
		float xRecPos = 0.f;
		const int yRecPos = mSpriteInfo.mSpritYoffset * mSpriteInfo.mWalkDownColumn;
		const int maxNumbersOfSprites = mSpriteInfo.mWalkNumberOfsprites;

		float animationMaxTime = .2f;

		mAnimCurrentTime += deltaTime;
		if (mAnimCurrentTime >= animationMaxTime)
		{
			xRecPos = mSpriteInfo.mSpritXoffset * mCurrentSprite++;
			UpdateRecSprite(true, xRecPos, yRecPos);
			mAnimCurrentTime = 0.f;
			if (mCurrentSprite >= maxNumbersOfSprites)
			{
				mCurrentSprite = 0;
			}
		}

		mPlayerPos.y += mMoveSpeed * deltaTime;
		lastMove = LastMove::LM_Down;
	}

	if (IsKeyDown(KeyboardKey::KEY_SPACE))
	{

		switch (lastMove)
		{
		case LastMove::LM_Rigth:
			mSpriteInfo.mAttackColumn = 45;
			break;
		case LastMove::LM_Left:
			mSpriteInfo.mAttackColumn = 47;
			break;
		case LastMove::LM_Up:
			mSpriteInfo.mAttackColumn = 46;
			break;
		case LastMove::LM_Down:
			mSpriteInfo.mAttackColumn = 44;
			break;
		case LastMove::none:
			break;
		default:
			break;
		}



		float xRecPos = 0.f;
		const int yRecPos = mSpriteInfo.mSpritYoffset * mSpriteInfo.mAttackColumn;
		const int maxNumbersOfSprites = mSpriteInfo.mAttackNumberOfsprites;

		float animationMaxTime = .2f;

		mAnimCurrentTime += deltaTime;
		if (mAnimCurrentTime >= animationMaxTime)
		{
			xRecPos = mSpriteInfo.mSpritXoffset * mCurrentSprite++;
			UpdateRecSprite(true, xRecPos, yRecPos);
			mAnimCurrentTime = 0.f;
			if (mCurrentSprite >= maxNumbersOfSprites)
			{
				mCurrentSprite = 0;
			}
		}
	}


	if (!bIsMoving)
	{
		Idle(deltaTime);
	}

	bIsMoving = false;

}

void Character::Idle(float deltaTime)
{

	float xRecPos = 0.f;
	const int yRecPos = 0;
	const int maxNumbersOfSprites = mSpriteInfo.mIdleNumberOfSprites;

	float animationMaxTime = .3f;

	mAnimCurrentTime += deltaTime;
	if (mAnimCurrentTime >= animationMaxTime)
	{
		
		xRecPos = mSpriteInfo.mSpritXoffset * (mCurrentSprite % maxNumbersOfSprites);
		mCurrentSprite++;
		UpdateRecSprite(false, xRecPos, yRecPos);
		mAnimCurrentTime = 0.f;
		if (mCurrentSprite >= maxNumbersOfSprites)
		{
			mCurrentSprite = 0;
		}
	}

}

void Character::UpdateRecSprite(bool isMoving, const float recX, const float recY)
{
	bIsMoving = isMoving;
	mRecSprite.x = recX;
	mRecSprite.y = recY;
}
