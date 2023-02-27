#include "Precompiled.h"
#include "ArriveBehavior.h"

#include "Agent.h"

using namespace AI;

std::pair<float, float> AI::ArriveBehavior::Calculate(Agent& agent)
{

	std::pair<float, float> agentToDestination;
	std::pair<float, float> seekForce;


	agentToDestination.first = agent.DestinationX - agent.posX;
	agentToDestination.second = agent.DestinationY - agent.posY;


	const float distanceToDestination = SMagnitude(agentToDestination);

	if (distanceToDestination <= 0.0f)
	{
		seekForce.first = 0.0f;
		seekForce.second = 0.0f;
		return seekForce;
	}

	//calculate desired velocity

	auto disiredVelocityX = (agentToDestination.first / distanceToDestination) * agent.maxSpeed;
	auto disiredVelocityY = (agentToDestination.second / distanceToDestination) * agent.maxSpeed;


	//getting closer -- Arriving condition
	if (distanceToDestination <= 300.0f)
	{
		const double DecelTweaker = 0.9;
		double speed = distanceToDestination / (DecelTweaker);
		speed = speed < agent.maxSpeed? speed : agent.maxSpeed;
		disiredVelocityX = agentToDestination.first * speed / distanceToDestination;
		disiredVelocityY = agentToDestination.second * speed / distanceToDestination;
	}

	seekForce.first = disiredVelocityX - agent.velovityX;
	seekForce.second = disiredVelocityY - agent.velovityY;


	if (IsDebug())
	{
		//Draw disired velocity
		DrawLine(agent.posX, agent.posY, agent.posX + disiredVelocityX, agent.posY + disiredVelocityY, YELLOW);

		//Draw Current velocity
		DrawLine(agent.posX, agent.posY, agent.posX + agent.velovityX, agent.posY + agent.velovityY, RED);
	}

	//acceleration = seekForce/mass;
	//velocity = acceleration * time;
	//position += velocity * time;

	return seekForce;
}
