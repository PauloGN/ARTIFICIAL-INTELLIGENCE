#include "Precompiled.h"
#include "SteeringModule.h"

AI::SteeringModule::SteeringModule(Agent& agent)
	:mAgent(agent)
{
}

std::pair<float, float> AI::SteeringModule::Calculate()
{
	std::pair<float, float> totalForce;

	for (auto& behavior: mBehaviors)
	{
		totalForce.first += behavior->Calculate(mAgent).first;
		totalForce.second += behavior->Calculate(mAgent).second;

	}

	return totalForce;
}
