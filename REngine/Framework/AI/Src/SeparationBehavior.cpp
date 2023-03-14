#include "Precompiled.h"
#include "SeparationBehavior.h"

#include "Agent.h"

using namespace AI;

std::pair<float, float> AI::SeparationBehavior::Calculate(Agent& agent)
{

	std::pair<float, float> separationForce;

	AIMath::Vector2 agentPos = { agent.posX, agent.posY };
	AIMath::Vector2 separationCouter;

	auto nbrs = agent.agentNeighbors;
	for(auto entity : nbrs)
	{

		if (entity == &agent)
		{
			continue;
		}

		AIMath::Vector2 entityPos = { entity->posX, entity->posY };
		auto entityToAgent = agentPos - entityPos;

		//Lengh of the vector to normalize
		auto lengthSqr = AIMath::MagnitudeSqr(entityToAgent);
		separationCouter += entityToAgent / lengthSqr;
	}

	if (IsDebug())
	{

	}

	separationCouter *= percentOfForce;

	separationForce.first = separationCouter.x;
	separationForce.second = separationCouter.y;

	return separationForce;
}

void AI::SeparationBehavior::SetSeparationForce(const float separationF)
{
	percentOfForce = separationF;
}