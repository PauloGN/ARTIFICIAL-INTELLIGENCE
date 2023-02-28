#include "Precompiled.h"
#include "ArriveBehavior.h"

#include "Agent.h"

using namespace AI;


namespace
{

	void CheckDistance(const float distanceToTarget, Agent& agent)
	{

		if (distanceToTarget >= 420.0f)
		{
			return;
		}


		if (distanceToTarget > 350.0f )
		{
			agent.maxSpeed = 250.0f;
		}
		else if (distanceToTarget > 300.0f)
		{
			agent.maxSpeed = 200.0f;
		}
		else if (distanceToTarget > 250.0f)
		{
			agent.maxSpeed = 150.0f;

		}
		else if (distanceToTarget > 200.0f)
		{
			agent.maxSpeed = 100.0f;
		}
		else if (distanceToTarget > 150.0f)
		{
			agent.maxSpeed = 70.0f;
		}
		else if (distanceToTarget > 100.0f)
		{
			agent.maxSpeed = 35.0f;
		}
		else if (distanceToTarget > 50.0f)
		{
			agent.maxSpeed = 22.0f;
		}
		else if (distanceToTarget <= 0.5f)
		{
			agent.maxSpeed = 0.02f;
		}
	}
}



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
	CheckDistance(distanceToDestination, agent);

	return seekForce;
}
