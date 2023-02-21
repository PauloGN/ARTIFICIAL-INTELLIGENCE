#include "Ninja.h"
#include "TypeId.h"
#include "NinjaStates.h"

namespace
{

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


Ninja::Ninja(AI::AIWorld& _world):Agent(_world, Types::T_NinjaChar)
{

	mNinjaSpritesheet = Texture2D();

	posX = 0.0f;
	posY = 0.0f;

	mRecSprite = Rectangle();
	mAnimCurrentTime = 0.f;
	mCurrentSprite = 0;

}


void Ninja::Load(const char* spriteName, const float initialSpeed, float spritXoffset, float spritYoffset, unsigned short IdleColumn, unsigned short WalkRightColumn, unsigned short WalkLeftColumn, unsigned short WalkUpColumn, unsigned short WalkDownColumn, unsigned short AttackColumn, unsigned short IdleNumberOfSprites, unsigned short WalkNumberOfsprites, unsigned short AttackNumberOfsprites)
{

	//Set up states
	mStateMachine = std::make_unique<AI::StateMachine<Ninja>>(*this);
	mStateMachine->AddState<NinjaIdle>();
	mStateMachine->AddState<NinjaHunting>();
	mStateMachine->ChangeState(NS_Idle);

	//load sprite sheet
	std::string fullPath;
	REng::ResourcesFullPath(spriteName, fullPath);
	mNinjaSpritesheet = LoadTexture(fullPath.c_str());

	mSpriteInfo.SetSpriteInfo(spritXoffset, spritYoffset, IdleColumn, WalkRightColumn, WalkLeftColumn, WalkUpColumn, WalkDownColumn, AttackColumn, IdleNumberOfSprites, WalkNumberOfsprites, AttackNumberOfsprites);

	//Rectangle initial position and size
	const int yInitialSpriteRowNumber = mSpriteInfo.mIdleColumn;//go down till get the Idle initial position
	mRecSprite.x = 0.f;
	mRecSprite.y = yInitialSpriteRowNumber * mSpriteInfo.mSpritYoffset;
	mRecSprite.width = mSpriteInfo.mSpritXoffset;
	mRecSprite.height = mSpriteInfo.mSpritYoffset;
}

void Ninja::Unload()
{
	mNinjaSpritesheet = Texture2D();

	posX = 0.0f;
	posY = 0.0f;

	mRecSprite = Rectangle();
	mAnimCurrentTime = 0.f;
	mCurrentSprite = 0;
}

void Ninja::Update(float deltaTime)
{
	//velovityX = 1;

	//float xRecPos = 0.f;
	//const int yRecPos = mSpriteInfo.mSpritYoffset * mSpriteInfo.mWalkRightColumn;
	//const int maxNumbersOfSprites = mSpriteInfo.mWalkNumberOfsprites;

	//mAnimCurrentTime += deltaTime;
	//if (mAnimCurrentTime >= mFrameDuration)
	//{
	//	xRecPos = mSpriteInfo.mSpritXoffset * mCurrentSprite++;
	//	UpdateRecSprite( xRecPos, yRecPos);
	//	mAnimCurrentTime = 0.f;
	//	if (mCurrentSprite >= maxNumbersOfSprites)
	//	{
	//		mCurrentSprite = 0;
	//	}
	//}

	//posX += velovityX * 100 * deltaTime;

	//lastMove = LastMove::LM_Rigth;

	mStateMachine->Update(deltaTime);

}

void Ninja::Render()
{
	DrawTextureRec(mNinjaSpritesheet, mRecSprite, { posX, posY }, WHITE);
	//DrawCircle(DestinationX, DestinationY, 5, RED);

}

void Ninja::ChangeState(NinjaState state)
{
}

void Ninja::Idle(float deltaTime)
{
	float xRecPos = 0.f;
	const int yRecPos = 0;
	const int maxNumbersOfSprites = mSpriteInfo.mIdleNumberOfSprites;

	float animationMaxTimeIdle = .3f;

	mAnimCurrentTime += deltaTime;
	if (mAnimCurrentTime >= animationMaxTimeIdle)
	{

		xRecPos = mSpriteInfo.mSpritXoffset * (mCurrentSprite % maxNumbersOfSprites);
		mCurrentSprite++;
		UpdateRecSprite(xRecPos, yRecPos);
		mAnimCurrentTime = 0.f;
		if (mCurrentSprite >= maxNumbersOfSprites)
		{
			mCurrentSprite = 0;
		}
	}
}

void Ninja::UpdateRecSprite(const float recX, const float recY)
{
	mRecSprite.x = recX;
	mRecSprite.y = recY;
}
