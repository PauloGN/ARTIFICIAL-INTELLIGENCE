#include "Precompiled.h"
#include "FleeBehavior.h"


#include "Agent.h"

using namespace AI;

std::pair<float, float> AI::FleeBehavior::Calculate(Agent& agent)
{

	std::pair<float, float> agentToFleePoint;
	std::pair<float, float> seekForce;

	agentToFleePoint.first = agent.DestinationX - agent.posX;
	agentToFleePoint.second = agent.DestinationY - agent.posY;

	const float distanceToFleePoint = SMagnitude(agentToFleePoint);

	//panic range
	if (distanceToFleePoint >= 500.0f)
	{
		seekForce.first = 0.0f;
		seekForce.second = 0.0f;
		return seekForce;
	}

	//calculate desired velocity

	const auto disiredVelocityX = -((agentToFleePoint.first / distanceToFleePoint) * agent.maxSpeed);
	const auto disiredVelocityY = -((agentToFleePoint.second / distanceToFleePoint) * agent.maxSpeed);

	seekForce.first = disiredVelocityX - agent.velovityX;
	seekForce.second = disiredVelocityY - agent.velovityY;

	if (IsDebug())
	{
		//Draw disired velocity
		DrawLine(agent.posX, agent.posY, agent.posX + disiredVelocityX, agent.posY + disiredVelocityY, YELLOW);

		//
		DrawLine(agent.posX, agent.posY, agent.posX + agent.velovityX, agent.posY + agent.velovityY, RED);
	}

	return seekForce;
}

