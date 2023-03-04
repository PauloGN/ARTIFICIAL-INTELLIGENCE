#include "Precompiled.h"
#include "WanderBehavior.h"

#include "Agent.h"

using namespace AI;

std::pair<float, float> AI::WanderBehavior::Calculate(Agent& agent)
{
	std::pair<float, float> wanderForce;//REETURN THIS PAIR

	//Randomize a position into the border, push it away with the seed to make a more ramdom
	AIMath::Vector2 newWaderTarget = mLocalWanderTarget + (AIMath::RandomUnitCircle(true) * mWanderJitter);

	//This point is not in the circle anymore so we need to normalize it.
	//snap back the new position to the circle
	newWaderTarget = AIMath::Normalize(newWaderTarget) * mWanderRadius;
	mLocalWanderTarget = newWaderTarget;

	//project new position forawrd in front of the agent
	newWaderTarget += AIMath::Vector2(0.0f, mWanderDistance);

	//getting the target in world space
	const auto WorldTransform = agent.GetWorldTransform();
	const auto worldWanderTarget = AIMath::TransformCoord(newWaderTarget, WorldTransform);

	//============================ SEEK =================================\\

	//target pos
	const AIMath::Vector2 agentToDestination = worldWanderTarget - AIMath::Vector2(agent.posX, agent.posY);
	const float distanceToDestination = Magnitude(agentToDestination);



	if (distanceToDestination <= 0.0f)
	{
		wanderForce.first = 0.0f;
		wanderForce.second = 0.0f;
		return wanderForce;
	}

	//calculate desired velocity

	const auto disiredVelocityX = (agentToDestination.x / distanceToDestination) * agent.maxSpeed;
	const auto disiredVelocityY = (agentToDestination.y / distanceToDestination) * agent.maxSpeed;

	wanderForce.first = disiredVelocityX - agent.velovityX;
	wanderForce.second = disiredVelocityY - agent.velovityY;

	if (mWanderDistance > 100.0f)
	{
		mWanderDistance *= 1;
	}


	if (IsDebug())
	{
		const auto wanderCenter = AIMath::TransformCoord({ 0.0f, mWanderDistance }, WorldTransform);

		DrawCircleLines(wanderCenter.x, wanderCenter.y, mWanderRadius, GREEN);
		DrawCircle( worldWanderTarget.x, worldWanderTarget.y, 5.0f, ORANGE);
		DrawLine(agent.posX, agent.posY, worldWanderTarget.x, worldWanderTarget.y, YELLOW);
	}

	return wanderForce;

}

void AI::WanderBehavior::Setup(const float radius, const float distance, const float jitter)
{
	mWanderDistance = distance;
	mWanderRadius = radius; 
	mWanderJitter = jitter;
}

