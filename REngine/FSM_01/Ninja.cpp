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
	mStateMachine->AddState<NinjaAttack>();
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

	mStateMachine->Update(deltaTime);

}

void Ninja::Render()
{
	DrawTextureRec(mNinjaSpritesheet, mRecSprite, { posX, posY }, WHITE);
	//DrawCircle(DestinationX, DestinationY, 5, RED);

}

void Ninja::ChangeState(NinjaState state)
{
	mStateMachine->ChangeState(state);
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

void Ninja::NinjaMovement(float deltaTime)
{

	int heading = 0;
	const float agentToDestinationX = DestinationX - posX;
	const float agentToDestinationY = DestinationY - posY;

	const float distance = REng::Math::Magnitude({ agentToDestinationX , agentToDestinationY });


	if (distance >= 5.0f)
	{

		//Normalize
		const float directionX = agentToDestinationX / distance;
		const float directionY = agentToDestinationY / distance;

		const int diffX = static_cast<int>(abs(DestinationX - posX));
		const int diffY = static_cast<int>(abs(DestinationY - posY));


		if (diffX >= diffY)
		{
			velovityX = directionX * 100.0f;
			velovityY = directionY * 50.0f;

			posX += velovityX * deltaTime;
			posY += velovityY * deltaTime;

			//check update animation
			if (posX > DestinationX)//go Left
			{

				heading = 1;

			}
			else if (posX <= DestinationX)//go Right
			{
				heading=  0;
			}
		}
		else if (diffX < diffY)
		{
			velovityX = directionX * 50.0f;
			velovityY = directionY * 100.0f;

			posY += velovityY * deltaTime;
			if (posY > DestinationY)//go Up
			{
				heading =  2;
			}

			else if (posY <= DestinationY)//go down
			{
				heading = 3;
			}
		}
	}


	if (heading == 0)// go Right
	{

		float xRecPos = 0.f;
		const int yRecPos = mSpriteInfo.mSpritYoffset * mSpriteInfo.mWalkRightColumn;
		const int maxNumbersOfSprites = mSpriteInfo.mWalkNumberOfsprites;

		mAnimCurrentTime += deltaTime;
		if (mAnimCurrentTime >= mFrameDuration)
		{
			xRecPos = mSpriteInfo.mSpritXoffset * mCurrentSprite++;
			UpdateRecSprite(xRecPos, yRecPos);
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
			UpdateRecSprite(xRecPos, yRecPos);
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
			UpdateRecSprite(xRecPos, yRecPos);
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
			UpdateRecSprite(xRecPos, yRecPos);
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
		Attack(deltaTime);
	}

}

void Ninja::Attack(float deltaTime)
{

	switch (lastMove)
	{
	case LastMove::LM_Rigth:
		mSpriteInfo.mAttackColumn = 47;
		break;
	case LastMove::LM_Left:
		mSpriteInfo.mAttackColumn = 45;
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
