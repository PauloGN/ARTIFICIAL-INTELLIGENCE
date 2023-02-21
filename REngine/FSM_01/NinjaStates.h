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

	Monster* mTarget;

};