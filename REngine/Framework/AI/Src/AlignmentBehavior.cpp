#include "Precompiled.h"
#include "AlignmentBehavior.h"

#include "Agent.h"

using namespace AI;

std::pair<float, float> AI::AlignmentBehavior::Calculate(Agent& agent)
{

	std::pair<float, float> separationForce;

	AIMath::Vector2 heading = { agent.headingX, agent.headingY };


	auto nbrs = agent.agentNeighbors;
	for (auto entity : nbrs)
	{

		AIMath::Vector2 entityHeading = { entity->headingX, entity->headingY };

		if (entity == &agent)
		{
			continue;
		}
		
		heading += entityHeading;
	}

	if (IsDebug())
	{

	}

	heading = AIMath::Normalize(heading);

	separationForce.first = (heading.x * agent.maxSpeed) * percentOfForce;
	separationForce.second = (heading.y * agent.maxSpeed) * percentOfForce;

	return separationForce;
}

void AI::AlignmentBehavior::SetAlignmentForce(const float separationF)
{
	percentOfForce = separationF;
}