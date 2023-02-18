#include "Enemy.h"
#include "EnemyState.h"
#include "TypeId.h"


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


void Enemy::Load(const char* spriteName, const float initialSpeed, float spritXoffset, float spritYoffset, unsigned short IdleColumn, unsigned short WalkRightColumn, unsigned short WalkLeftColumn, unsigned short WalkUpColumn, unsigned short WalkDownColumn, unsigned short AttackColumn, unsigned short IdleNumberOfSprites, unsigned short WalkNumberOfsprites, unsigned short AttackNumberOfsprites)
{

	//Set up states
	mStateMachine = std::make_unique<AI::StateMachine<Enemy>>(*this);
	mStateMachine->AddState<EnemyIdle>();
	mStateMachine->AddState<EnemyWalk>();
	mStateMachine->AddState<EnemyAttack>();
	mStateMachine->ChangeState(S_Idle);


	//load sprite sheet
	std::string fullPath;
	REng::ResourcesFullPath(spriteName, fullPath);
	mEnemySpritesheet = LoadTexture(fullPath.c_str());
	bIsMoving = false;

	mSpriteInfo.SetSpriteInfo(spritXoffset, spritYoffset, IdleColumn, WalkRightColumn, WalkLeftColumn, WalkUpColumn, WalkDownColumn, AttackColumn, IdleNumberOfSprites, WalkNumberOfsprites, AttackNumberOfsprites);

	//Set Initial Speed
	initialSpeed > 1.f ? mMoveSpeed = initialSpeed : mMoveSpeed = 45.f;

	//Rectangle initial position and size
	const int yInitialSpriteRowNumber = mSpriteInfo.mIdleColumn;//go down till get the Idle initial position
	mRecSprite.x = 0.f;
	mRecSprite.y = yInitialSpriteRowNumber * mSpriteInfo.mSpritYoffset;
	mRecSprite.width = mSpriteInfo.mSpritXoffset;
	mRecSprite.height = mSpriteInfo.mSpritYoffset;

}

void Enemy::Unload()
{

	mMoveSpeed = 0.f;
	mEnemySpritesheet = Texture2D();
	
	posX = 0.0f;
	posY = 0.0f;

	mRecSprite = Rectangle();
	bIsMoving = false;
	mAnimCurrentTime = 0.f;
	mCurrentSprite = 0;

}

void Enemy::Update(float deltaTime)
{

	mStateMachine->Update(deltaTime);

}

void Enemy::Render()
{

	DrawTextureRec(mEnemySpritesheet, mRecSprite, {posX, posY}, WHITE);
	DrawCircle(DestinationX, DestinationY, 5, RED);
}

void Enemy::ChangeState(State state)
{

	mStateMachine->ChangeState(state);

}

Enemy::Enemy(AI::AIWorld world):Agent(world, Types::T_NPC)
{
	//position

	posY = 64.0f;
	posX = 32.0f;

	mMoveSpeed = 0.f;
	mEnemySpritesheet = Texture2D();
	
	mRecSprite = Rectangle();
	bIsMoving = false;
	mAnimCurrentTime = 0.f;
	mCurrentSprite = 0;
}


void Enemy::PlayerMovement(float deltaTime, int heading)
{

	if ( heading == 0)// go Right
	{

		float xRecPos = 0.f;
		const int yRecPos = mSpriteInfo.mSpritYoffset * mSpriteInfo.mWalkRightColumn;
		const int maxNumbersOfSprites = mSpriteInfo.mWalkNumberOfsprites;

		mAnimCurrentTime += deltaTime;
		if (mAnimCurrentTime >= mFrameDuration)
		{
			xRecPos = mSpriteInfo.mSpritXoffset * mCurrentSprite++;
			UpdateRecSprite(true, xRecPos, yRecPos);
			mAnimCurrentTime = 0.f;
			if (mCurrentSprite >= maxNumbersOfSprites)
			{
				mCurrentSprite = 0;
			}
		}

		lastMove = LastMove::LM_Rigth;
	}


	if (heading == 1)// go left
	{
		float xRecPos = 0.f;
		const int yRecPos = mSpriteInfo.mSpritYoffset * mSpriteInfo.mWalkLeftColumn;
		const int maxNumbersOfSprites = mSpriteInfo.mWalkNumberOfsprites;

		mAnimCurrentTime += deltaTime;
		if (mAnimCurrentTime >= mFrameDuration)
		{
			xRecPos = mSpriteInfo.mSpritXoffset * mCurrentSprite++;
			UpdateRecSprite(true, xRecPos, yRecPos);
			mAnimCurrentTime = 0.f;
			if (mCurrentSprite >= maxNumbersOfSprites)
			{
				mCurrentSprite = 0;
			}
		}

		lastMove = LastMove::LM_Left;
	}

	if (heading == 2) //go Up
	{
		float xRecPos = 0.f;
		const int yRecPos = mSpriteInfo.mSpritYoffset * mSpriteInfo.mWalkUpColumn;
		const int maxNumbersOfSprites = mSpriteInfo.mWalkNumberOfsprites;

		mAnimCurrentTime += deltaTime;
		if (mAnimCurrentTime >= mFrameDuration)
		{
			xRecPos = mSpriteInfo.mSpritXoffset * mCurrentSprite++;
			UpdateRecSprite(true, xRecPos, yRecPos);
			mAnimCurrentTime = 0.f;
			if (mCurrentSprite >= maxNumbersOfSprites)
			{
				mCurrentSprite = 0;
			}
		}

		lastMove = LastMove::LM_Up;
	}


	if (heading == 3)//Go down
	{
		float xRecPos = 0.f;
		const int yRecPos = mSpriteInfo.mSpritYoffset * mSpriteInfo.mWalkDownColumn;
		const int maxNumbersOfSprites = mSpriteInfo.mWalkNumberOfsprites;

		mAnimCurrentTime += deltaTime;
		if (mAnimCurrentTime >= mFrameDuration)
		{
			xRecPos = mSpriteInfo.mSpritXoffset * mCurrentSprite++;
			UpdateRecSprite(true, xRecPos, yRecPos);
			mAnimCurrentTime = 0.f;
			if (mCurrentSprite >= maxNumbersOfSprites)
			{
				mCurrentSprite = 0;
			}
		}

		lastMove = LastMove::LM_Down;
	}


	if (IsKeyDown(KeyboardKey::KEY_HOME))
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


		mAnimCurrentTime += deltaTime;
		if (mAnimCurrentTime >= mFrameDuration)
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

}

void Enemy::Idle(float deltaTime)
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
		UpdateRecSprite(false, xRecPos, yRecPos);
		mAnimCurrentTime = 0.f;
		if (mCurrentSprite >= maxNumbersOfSprites)
		{
			mCurrentSprite = 0;
		}
	}

}

void Enemy::Attack()
{}

void Enemy::UpdateRecSprite(bool isMoving, const float recX, const float recY)
{
	bIsMoving = isMoving;
	mRecSprite.x = recX;
	mRecSprite.y = recY;
}
