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

		std::pair<float, float> TempTotalForce = behavior->Calculate(mAgent);

		totalForce.first += TempTotalForce.first;
		totalForce.second += TempTotalForce.second;

	}

	return totalForce;
}
