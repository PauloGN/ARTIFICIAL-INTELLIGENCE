#pragma once
#include <AI.h>
#include <REngine.h>

class Monster;

class Ninja : public AI::Agent
{
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

			mIdleColumn = IdleColumn;
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
	struct NinjaAtributes
	{
		int goldAtTheBank = 0.0f;
		int goldInSaddlebag = 0.0f;
		int tiredness = 0.0f;

		//Saddlebage
		void IncreaseSaddlebagGold() { goldInSaddlebag += 10; }
		//void DecreaseSaddlebagGold();
		//
		////Bank
		//void IncreaseBankGold();
		//void DecreaseBankGold();
		//
		////Life
		void GettingRest() {};
		void GettingTired(int lifeDmg) { tiredness += lifeDmg; }

	};

public:

	enum NinjaState
	{
		NS_Idle,
		NS_GoHuting,
		NS_Attack,
		NS_GoBank,
		NS_GoShelter
	};

	Ninja(AI::AIWorld& _world);

	void Load(const char* spriteName, const float initialSpeed, float spritXoffset, float spritYoffset, unsigned short IdleColumn, unsigned short WalkRightColumn, unsigned short WalkLeftColumn, unsigned short WalkUpColumn, unsigned short WalkDownColumn, unsigned short AttackColumn, unsigned short IdleNumberOfSprites, unsigned short WalkNumberOfsprites, unsigned short AttackNumberOfsprites);

	void Unload();
	void Update(float deltaTime);
	void Render();
	void ChangeState(NinjaState state);//state machine

	NinjaAtributes ninjaAtribultes;

	//State functions
	void Idle(float deltaTime);
	void NinjaMovement(float deltaTime);

	void Attack(float deltaTime);
	void SetCurrentTarget(Monster* target) { mCurrentTarget = target; }
	Monster* GetCurrentTarget() {return mCurrentTarget; }

private:

	//States
	std::unique_ptr<AI::StateMachine<Ninja>> mStateMachine;
	Monster* mCurrentTarget = nullptr;

	//Sprites
	Rectangle mRecSprite;
	Texture2D mNinjaSpritesheet;
	SpriteInfo mSpriteInfo;

	//Animation
	float mAnimCurrentTime;
	int mCurrentSprite;
	const float mFrameDuration = .2f;
	void UpdateRecSprite(const float recX, const float recY);
};
