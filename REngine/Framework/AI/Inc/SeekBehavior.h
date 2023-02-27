#pragma once
#include "SteeringBehavior.h"


namespace AI
{
	class SeekBehavior : public SteeringBehavior
	{
	public:

		virtual std::pair<float, float> Calculate(Agent& agent) override;	
	};
}