#pragma once

#include "Enemy.h"



class EnemyIdle :public AI::State<Enemy>
{
public:

	virtual void Enter(Enemy& agent)override;
	virtual void Update(Enemy& agent, float deltaTime)override;
	virtual void Exit(Enemy& agent)override;

private:

	float mWaitTime;
};


class EnemyWalk :public AI::State<Enemy>
{
public:

	virtual void Enter(Enemy& agent)override;
	virtual void Update(Enemy& agent, float deltaTime)override;
	virtual void Exit(Enemy& agent)override;

};

class EnemyAttack :public AI::State<Enemy>
{
public:

	virtual void Enter(Enemy& agent)override;
	virtual void Update(Enemy& agent, float deltaTime)override;
	virtual void Exit(Enemy& agent)override;

private:

	 

	class Pickup* mPickupTarget;

};