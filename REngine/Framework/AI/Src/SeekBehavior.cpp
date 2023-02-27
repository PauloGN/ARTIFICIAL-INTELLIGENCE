#include "Precompiled.h"
#include "SeekBehavior.h"

#include "Agent.h"

using namespace AI;

std::pair<float, float> AI::SeekBehavior::Calculate(Agent& agent)
{

	std::pair<float, float> agentToDestination;
	std::pair<float, float> seekForce;


	agentToDestination.first = agent.DestinationX - agent.posX;
	agentToDestination.second = agent.DestinationY - agent.posY;


	const float distanceToDestination = SMagnitude(agentToDestination);

	if (distanceToDestination <= 0.0f )
	{
		seekForce.first = 0.0f;
		seekForce.second = 0.0f;
		return seekForce;
	}

	//calculate desired velocity

	const auto disiredVelocityX = (agentToDestination.first / distanceToDestination) * agent.maxSpeed;
	const auto disiredVelocityY = (agentToDestination.second / distanceToDestination) * agent.maxSpeed;

	seekForce.first = disiredVelocityX - agent.velovityX;
	seekForce.second = disiredVelocityY - agent.velovityY;


	if (IsDebug())
	{
		//Draw disired velocity
		DrawLine(agent.posX, agent.posY ,agent.posX + disiredVelocityX, agent.posY + disiredVelocityY, YELLOW);

		//
		DrawLine(agent.posX, agent.posY, agent.posX + agent.velovityX, agent.posY + agent.velovityY, RED);
	}

	return seekForce;
}

