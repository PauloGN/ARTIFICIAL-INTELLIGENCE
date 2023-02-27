#pragma once
#include "SteeringBehavior.h"


namespace AI
{
	class ArriveBehavior : public SteeringBehavior
	{
	public:

		virtual std::pair<float, float> Calculate(Agent& agent) override;
	};
}