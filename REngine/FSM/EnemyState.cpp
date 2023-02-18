#include "EnemyState.h"
#include "Pickup.h"
//============================================================================================	Idle

void EnemyIdle::Enter(Enemy& agent)
{
	mWaitTime = 3.0f;

}

void EnemyIdle::Update(Enemy & agent, float deltaTime)
{

	mWaitTime -= deltaTime;
	
	if(mWaitTime <= 0.0f)
	{
		agent.ChangeState(Enemy::S_Walk);
	}

	agent.Idle(deltaTime);
	DrawText("Idle", agent.posX, agent.posY - 20, 16, WHITE);

}

void EnemyIdle::Exit(Enemy & agent)
{}


//====================================================================================	Moviment Section

void EnemyWalk::Enter(Enemy& agent)
{
	float randomX = REng::Math::RandomFloat(100.0f, 1500.0f);
	float randomY = REng::Math::RandomFloat(100.0f, 800);

	agent.DestinationX = randomX;
	agent.DestinationY = randomY;
}

void EnemyWalk::Update(Enemy & agent, float deltaTime)
{
	
	const float agentToDestinationX = agent.DestinationX - agent.posX;
	const float agentToDestinationY = agent.DestinationY - agent.posY;

	const float distance = REng::Math::Magnitude({ agentToDestinationX , agentToDestinationY });


	if (distance >= 5.0f)
	{

		//Normalize
		const float directionX = agentToDestinationX / distance;
		const float directionY = agentToDestinationY / distance;

		const int diffX = static_cast<int>(abs(agent.DestinationX - agent.posX));
		const int diffY = static_cast<int>(abs(agent.DestinationY - agent.posY));


		if (diffX >= diffY)
		{
			agent.velovityX = directionX * 100.0f;
			agent.velovityY = directionY * 50.0f;

			agent.posX += agent.velovityX * deltaTime;
			agent.posY += agent.velovityY * deltaTime;

			//check update animation
			if (agent.posX > agent.DestinationX)//go Left
			{

				agent.PlayerMovement(deltaTime, 1);

			}
			else if (agent.posX <= agent.DestinationX)//go Right
			{
				agent.PlayerMovement(deltaTime, 0);

			}
		}
		else if(diffX < diffY)
		{
			agent.velovityX = directionX * 50.0f;
			agent.velovityY = directionY * 100.0f;

			agent.posY += agent.velovityY * deltaTime;
			if (agent.posY > agent.DestinationY)//go Up
			{
				agent.PlayerMovement(deltaTime, 2);

			}

			else if (agent.posY <= agent.DestinationY)//go down
			{
				agent.PlayerMovement(deltaTime, 3);

			}
		}

	}
	else
	{
		agent.ChangeState(Enemy::S_Idle);
	}
}

void EnemyWalk::Exit(Enemy & agent)
{}


//===========================================        Attack


void EnemyAttack::Enter(Enemy& agent)
{
	
	std::vector<AI::Entity*> entities = agent.world.GetAllEntitiesOfType(Types::T_Apple);
	float minDistance = FLT_MAX;

	for (auto entity: entities)
	{

		const REng::Math::Vector2 agentPos(agent.posX, agent.posY);
		const REng::Math::Vector2 entityPos(entity->posX, entity->posY);

		float distanceSqr = REng::Math::MagnitudeSqr(agentPos - entityPos);

		if (distanceSqr < minDistance)
		{
			minDistance = distanceSqr;
			mPickupTarget = static_cast<Pickup*>(entity);
		}

	}


}

void EnemyAttack::Update(Enemy & agent, float deltaTime)
{


	if (mPickupTarget)
	{

		agent.DestinationX = mPickupTarget->posX;
		agent.DestinationY = mPickupTarget->posY;

		const REng::Math::Vector2 agentPos(agent.posX, agent.posY);
		const REng::Math::Vector2 targetPos(mPickupTarget->posX, mPickupTarget->posY);

		const auto agentToTargetDistance = targetPos - agentPos;
		const float distance = REng::Math::Magnitude(agentToTargetDistance);

		if (distance > 5.0f)
		{
			const auto direction = agentToTargetDistance / distance;
			agent.velovityX = direction.x * 200.0f;
			agent.velovityY = direction.y * 200.0f;

			const int diffX = static_cast<int>(abs(agent.DestinationX - agent.posX));
			const int diffY = static_cast<int>(abs(agent.DestinationY - agent.posY));


			if (diffX >= diffY)
			{
				agent.velovityX = direction.x * 100.0f;
				agent.velovityY = direction.y * 50.0f;

				agent.posX += agent.velovityX * deltaTime;
				agent.posY += agent.velovityY * deltaTime;

				//check update animation
				if (agent.posX > agent.DestinationX)//go Left
				{

					agent.PlayerMovement(deltaTime, 1);

				}
				else if (agent.posX <= agent.DestinationX)//go Right
				{
					agent.PlayerMovement(deltaTime, 0);

				}
			}
			else if (diffX < diffY)
			{
				agent.velovityX = direction.x * 50.0f;
				agent.velovityY = direction.y * 100.0f;

				agent.posY += agent.velovityY * deltaTime;
				if (agent.posY > agent.DestinationY)//go Up
				{
					agent.PlayerMovement(deltaTime, 2);

				}

				else if (agent.posY <= agent.DestinationY)//go down
				{
					agent.PlayerMovement(deltaTime, 3);

				}
			}

		}
		else
		{
			agent.Attack();
			mPickupTarget->Consume();
			agent.ChangeState(Enemy::S_Idle);
		}
	}

}

void EnemyAttack::Exit(Enemy & agent)
{}
