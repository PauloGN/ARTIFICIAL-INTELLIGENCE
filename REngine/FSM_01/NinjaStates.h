#pragma once
#include "Ninja.h"

//=================================================      IDLE
class NinjaIdle: public AI::State<Ninja>
{
public:

	void Enter(Ninja& agent) override;
	void Update(Ninja& agent, float deltaTime) override;
	void Exit(Ninja& agent) override;

private:

	float mWaitTime = 0.0f;

};


//==============================================     Hunting

class Monster;
class NinjaHunting : public AI::State<Ninja>
{
public:

	void Enter(Ninja& agent) override;
	void Update(Ninja& agent, float deltaTime) override;
	void Exit(Ninja& agent) override;

private:

	Monster* mTarget = nullptr;

};


//==============================================     Attack

class NinjaAttack : public AI::State<Ninja>
{
public:

	void Enter(Ninja& agent) override;
	void Update(Ninja& agent, float deltaTime) override;
	void Exit(Ninja& agent) override;

private:
	float mWaitTime = 0.0f;
	Monster* mTarget = nullptr;

};


//==============================================     Bank

class Bank;
class NinjaGoBank : public AI::State<Ninja>
{
public:

	void Enter(Ninja& agent) override;
	void Update(Ninja& agent, float deltaTime) override;
	void Exit(Ninja& agent) override;

private:

	Bank* mBank = nullptr;

};