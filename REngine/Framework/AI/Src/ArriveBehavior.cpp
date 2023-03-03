#include "Precompiled.h"
#include "ArriveBehavior.h"

#include "Agent.h"

using namespace AI;


namespace
{

	enum Deceleration	{ slow = 3, normal = 2, fast =1	};

}



std::pair<float, float> AI::ArriveBehavior::Calculate(Agent& agent)
{

	std::pair<float, float> toTarget;
	std::pair<float, float> seekForce;

	toTarget.first = agent.DestinationX - agent.posX;
	toTarget.second = agent.DestinationY - agent.posY;

	const float distanceToDestination = SMagnitude(toTarget);

	if (distanceToDestination <= 0.0f)
	{
		seekForce.first = 0.0f;
		seekForce.second = 0.0f;
		return seekForce;
	}

	 double decelTweeker = 0.3f;

	if (distanceToDestination <= controlDecelRadius)
	{
		DrawCircleLines(agent.DestinationX, agent.DestinationY, controlDecelRadius, PURPLE);
		decelTweeker = controlDecelTweker;
	}

	double speed = distanceToDestination / decelTweeker * (double)fast;



	//get a velocity always lower than maxSpeed
	speed = speed < agent.maxSpeed ? speed : agent.maxSpeed;

	auto disiredVelocityX = toTarget.first * speed / distanceToDestination;
	auto disiredVelocityY = toTarget.second * speed / distanceToDestination;

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

void AI::ArriveBehavior::SetDecel(const float tweeker, const float radius)
{
	controlDecelTweker = tweeker;
	controlDecelRadius = radius;
}
