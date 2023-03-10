#include "Precompiled.h"
#include "CohesionBehavior.h"

#include "Agent.h"

using namespace AI;

std::pair<float, float> AI::CohesionBehavior::Calculate(Agent& agent)
{

	std::pair<float, float> cohesionForce;
	int counter = 0;

	AIMath::Vector2 centerOfmass;


	auto nbrs = agent.agentNeighbors;
	for (auto entity : nbrs)
	{
		AIMath::Vector2 entityPos = { entity->posX, entity->posY };

		centerOfmass += entityPos;
		counter++;
	}

	AIMath::Vector2 agentPos = {agent.posX, agent.posY};


	if (counter > 1)
	{
		centerOfmass /= counter;
		auto disiredVelocity = AIMath::Normalize((centerOfmass - agentPos)* agent.maxSpeed);

		cohesionForce.first = (disiredVelocity.x - agent.velovityX) * percentOfForce;
		cohesionForce.second = (disiredVelocity.y - agent.velovityY) * percentOfForce;
	}


	return cohesionForce;
}

void AI::CohesionBehavior::SetCohesionForce(const float percentF)
{
	percentOfForce = percentF;
}