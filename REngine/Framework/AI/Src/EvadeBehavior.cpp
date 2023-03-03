#include "Precompiled.h"
#include "EvadeBehavior.h"


#include "Agent.h"

using namespace AI;

std::pair<float, float> AI::EvadeBehavior::Calculate(Agent& agent)
{

	std::pair<float, float> agentToEvadePoint;
	std::pair<float, float> seekForce;

	assert(agent.otherAgent != nullptr, "OtherAgent must be set");

	//                             origem                 + velocidade                  * ponto futuro
	float otherAgentDestinationX = agent.otherAgent->posX + agent.otherAgent->velovityX + predictionPoint; // future point prediction
	float otherAgentDestinationY = agent.otherAgent->posY + agent.otherAgent->velovityY + predictionPoint;


	agentToEvadePoint.first = otherAgentDestinationX - agent.posX;
	agentToEvadePoint.second = otherAgentDestinationY - agent.posY;

	const float distanceToFleePoint = SMagnitude(agentToEvadePoint);

	//panic range
	if (distanceToFleePoint >= 300.0f)
	{
		seekForce.first = 0.0f;
		seekForce.second = 0.0f;
		return seekForce;
	}

	//calculate desired velocity

	const auto disiredVelocityX = -((agentToEvadePoint.first / distanceToFleePoint) * agent.maxSpeed);
	const auto disiredVelocityY = -((agentToEvadePoint.second / distanceToFleePoint) * agent.maxSpeed);

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

void AI::EvadeBehavior::SetPredictionPoint(const float prediction)
{

	if (predictionPoint < 0.0f)
	{
		predictionPoint = 0.0f;
	}

	predictionPoint = prediction;
}

