#include "Precompiled.h"
#include "PursuitBehavior.h"

#include "Agent.h"

using namespace AI;

std::pair<float, float> AI::PursuitBehavior::Calculate(Agent& agent)
{

	std::pair<float, float> agentToDestination;
	std::pair<float, float> seekForce;

	assert(agent.otherAgent != nullptr, "OtherAgent must be set");
	//                             origem                 + velocidade                  * ponto futuro
	float otherAgentDestinationX = agent.otherAgent->posX + agent.otherAgent->velovityX + mPredictionPoint; // future point prediction
	float otherAgentDestinationY = agent.otherAgent->posY + agent.otherAgent->velovityY + mPredictionPoint;

	agentToDestination.first = otherAgentDestinationX - agent.posX;
	agentToDestination.second = otherAgentDestinationY - agent.posY;

	const float distanceToDestination = SMagnitude(agentToDestination);

	if (distanceToDestination <= 0.0f)
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
		DrawLine(agent.posX, agent.posY, agent.posX + disiredVelocityX, agent.posY + disiredVelocityY, YELLOW);

		//
		DrawLine(agent.posX, agent.posY, agent.posX + agent.velovityX, agent.posY + agent.velovityY, RED);
	}

	return seekForce;
}


void AI::PursuitBehavior::SetPredictionPoint(const float prediction)
{

	if (mPredictionPoint < 0.0f)
	{
		mPredictionPoint = 0.0f;
	}

	mPredictionPoint = prediction;

}