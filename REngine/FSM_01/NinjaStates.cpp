#include "NinjaStates.h"
#include "Monster.h"
#include "TypeId.h"

namespace
{

	void DrawUI(Ninja& NinjaRef)
	{
		DrawText("Idle", NinjaRef.posX + 10, NinjaRef.posY + 50, 16, WHITE);
	}

}

/// <summary>
/// IDLE
/// </summary>
/// <param name="agent">
/// 
/// from Idle agent can go Home, go shelter or go hunting
/// 
/// 
/// </param>

void NinjaIdle::Enter(Ninja& agent)
{
	mWaitTime = 3.0f;
}

void NinjaIdle::Update(Ninja& agent, float deltaTime)
{

	mWaitTime -= deltaTime;
	if (mWaitTime <= 0.0f)
	{
		if(agent.ninjaAtribultes.tiredness <= 10)
		{
			//Hunter
		}
		else
		{
			//GoShelter
		}

		if (agent.ninjaAtribultes.goldInSaddlebag > 100)
		{
			//GoBank
		}
	}

	agent.Idle(deltaTime);

	DrawUI(agent);

}

void NinjaIdle::Exit(Ninja& agent)
{
}

/// <summary>
/// Hunting
/// </summary>
/// <param name="agent"></param>

void NinjaHunting::Enter(Ninja& agent)
{
	std::vector<AI::Entity*> entities = agent.world.GetAllEntitiesOfType(Types::T_Monster);
	float minDistance = FLT_MAX;

	for (auto entity : entities)
	{

		const REng::Math::Vector2 agentPos({ agent.posX, agent.posY });
		const REng::Math::Vector2 entityPos({ entity->posX, entity->posY});

		float distanceSqr = REng::Math::MagnitudeSqr(agentPos - entityPos);
		if (distanceSqr < minDistance)
		{
			minDistance = distanceSqr;
			mTarget = static_cast<Monster*>(entity);
		}
	}
}

void NinjaHunting::Update(Ninja& agent, float deltaTime)
{

	if (mTarget)
	{
		//Vector
		const REng::Math::Vector2 agentPos({ agent.posX, agent.posY });
		const REng::Math::Vector2 targetPos({ mTarget->posX, mTarget->posY });

		const auto agentToTarget = targetPos - agentPos;
		const float distance = REng::Math::Magnitude(agentToTarget);

		if (distance > 5.0f)
		{
			const auto direction = agentToTarget / distance;
			
			//speed
			agent.velovityX = direction.x * 200.0f;
			agent.velovityY = direction.y * 200.0f;
			//Move
			agent.posX += agent.velovityX * deltaTime;
			agent.posY += agent.velovityY * deltaTime;

			//Animation
			//agent.UpdateAnimation(deltaTime);
		}
		else
		{
			//agent.EatBrain();
			//mTarget->Consume();

			agent.ChangeState(Ninja::NS_Idle);
		}
	}

}

void NinjaHunting::Exit(Ninja& agent)
{
}
