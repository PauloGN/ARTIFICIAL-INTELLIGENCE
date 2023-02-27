#pragma once
#include "SteeringBehavior.h"


namespace AI
{
	class PursuitBehavior : public SteeringBehavior
	{
	public:

		virtual std::pair<float, float> Calculate(Agent& agent) override;
	};
}