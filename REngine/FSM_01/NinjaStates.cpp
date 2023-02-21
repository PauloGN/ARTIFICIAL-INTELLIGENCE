#include "NinjaStates.h"
#include "Monster.h"
#include "TypeId.h"
#include "Bank.h"

namespace
{

	void DrawUI(Ninja& NinjaRef, const char*clue )
	{
		std::string myGold = "My Gold: " + std::to_string(NinjaRef.ninjaAtribultes.goldInSaddlebag);
		std::string myBank = "Gold at the Bank: " + std::to_string(NinjaRef.ninjaAtribultes.goldAtTheBank);
		std::string myLife = "Tiredness level: " +  std::to_string( NinjaRef.ninjaAtribultes.tiredness);

		DrawText(clue, NinjaRef.posX + 10, NinjaRef.posY + 50, 16, WHITE);
		DrawText(myGold.c_str(), 32, 10, 18, YELLOW);
		DrawText(myBank.c_str(), 160, 10, 18, YELLOW);
		DrawText(myLife.c_str(), 384,  10, 18, YELLOW);
	}

}


//===============================================================================							 IDLE
/// </summary>
/// <param name="agent">
/// 
/// from Idle agent can go Home, go shelter or go hunting


void NinjaIdle::Enter(Ninja& agent)
{
	mWaitTime = 3.0f;
}

void NinjaIdle::Update(Ninja& agent, float deltaTime)
{

	mWaitTime -= deltaTime;
	if (mWaitTime <= 0.0f)
	{
		if(agent.ninjaAtribultes.tiredness <= 100 && agent.ninjaAtribultes.goldInSaddlebag <= 100)
		{
			agent.ChangeState(Ninja::NS_GoHuting);
		}
		else
		{
			//GoShelter
		}

		if (agent.ninjaAtribultes.goldInSaddlebag > 100)
		{
			agent.ChangeState(Ninja::NS_GoBank);
		}
	}

	agent.Idle(deltaTime);

	DrawUI(agent, "Idle");

}

void NinjaIdle::Exit(Ninja& agent)
{
}


//==============================================================================================			 Hunting
/// </summary>
/// <param name="agent"></param>

void NinjaHunting::Enter(Ninja& agent)
{

	//Hunting drives to exhaustion
	agent.ninjaAtribultes.GettingTired(4);

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

		agent.DestinationX = mTarget->posX;
		agent.DestinationY = mTarget->posY;

		const auto agentToTarget = targetPos - agentPos;
		const float distance = REng::Math::Magnitude(agentToTarget);

		if (distance > 5.0f)
		{
			const auto direction = agentToTarget / distance;
			
			//speed
			agent.velovityX = direction.x * 200.0f;
			agent.velovityY = direction.y * 200.0f;

			//Movement & Animation
			agent.NinjaMovement(deltaTime);
		}
		else
		{
			agent.SetCurrentTarget(mTarget);
			agent.ChangeState(Ninja::NS_Attack);
		}
	}

	DrawUI(agent, "Hunting");

}

void NinjaHunting::Exit(Ninja& agent)
{
}


//=====================================================================================				 Attack
/// </summary>
/// <param name="agent"></param>

void NinjaAttack::Enter(Ninja& agent)
{
	mWaitTime = 3.0f;

}

void NinjaAttack::Update(Ninja& agent, float deltaTime)
{

	mWaitTime -= deltaTime;
	if (mWaitTime <= 0.0f)
	{

		//Get a monster to attack
		mTarget = agent.GetCurrentTarget();
			if (mTarget)
			{
				mTarget->Die();
			}

		agent.ninjaAtribultes.IncreaseSaddlebagGold();
		

		if (agent.ninjaAtribultes.tiredness <= 100)
		{
			agent.ChangeState(Ninja::NS_Idle);
		}
		else
		{
			//GoShelter
		}

		if (agent.ninjaAtribultes.goldInSaddlebag > 100)
		{
			agent.ChangeState(Ninja::NS_GoBank);
		}
			return;
	}

	agent.Attack(deltaTime);
	DrawUI(agent, "Attacking");

}

void NinjaAttack::Exit(Ninja& agent)
{
	//Hunting drives to exhaustion
	agent.ninjaAtribultes.GettingTired(2);
}


//=====================================================================================				 Go To the Bank
/// </summary>
/// <param name="agent"></param>


void NinjaGoBank::Enter(Ninja& agent)
{

	//go to the bank is stressfull
	agent.ninjaAtribultes.GettingTired(1);

	std::vector<AI::Entity*> entities = agent.world.GetAllEntitiesOfType(Types::T_Bank);
	float minDistance = FLT_MAX;

	for (auto entity : entities)
	{
		const REng::Math::Vector2 agentPos({ agent.posX, agent.posY });
		const REng::Math::Vector2 entityPos({ entity->posX, entity->posY });

		float distanceSqr = REng::Math::MagnitudeSqr(agentPos - entityPos);
		if (distanceSqr < minDistance)
		{
			minDistance = distanceSqr;
			mBank = static_cast<Bank*>(entity);
		}
	}

}

void NinjaGoBank::Update(Ninja& agent, float deltaTime)
{

	//Go to the Bank
	if (mBank)
	{
		//Vector
		const REng::Math::Vector2 agentPos({ agent.posX, agent.posY });
		const REng::Math::Vector2 targetPos({ mBank->posX, mBank->posY });

		agent.DestinationX = mBank->posX;
		agent.DestinationY = mBank->posY;

		const auto agentToTarget = targetPos - agentPos;
		const float distance = REng::Math::Magnitude(agentToTarget);

		if (distance > 5.0f)
		{
			const auto direction = agentToTarget / distance;

			//speed
			agent.velovityX = direction.x * 100.0f;
			agent.velovityY = direction.y * 100.0f;

			//Movement & Animation
			agent.NinjaMovement(deltaTime);
		}
		else
		{
			agent.ninjaAtribultes.IncreaseBankGold();
		}

	}

	if (agent.ninjaAtribultes.tiredness <= 100 && agent.ninjaAtribultes.goldInSaddlebag <= 100)
	{
		agent.ChangeState(Ninja::NS_GoHuting);
	}
	else
	{
		//GoShelter
	}


	DrawUI(agent, "Go banking");

}

void NinjaGoBank::Exit(Ninja& agent)
{
}
