#include "Precompiled.h"
#include "WanderBehavior.h"
#include "raymath.h"

#include "Agent.h"

using namespace AI;

std::pair<float, float> AI::WanderBehavior::Calculate(Agent& agent)
{

	std::pair<float, float> agentToDestination;
	std::pair<float, float> seekForce;



	return seekForce;
}

void AI::WanderBehavior::Setup(const float radius, const float distance, const float jitter)
{
	mWanderDistance = distance;
	mWanderRadius = radius;
	mWanderJitter = jitter;


}

