#pragma once
#include "SteeringBehavior.h"


namespace AI
{
	class ArriveBehavior : public SteeringBehavior
	{
	public:

		virtual std::pair<float, float> Calculate(Agent& agent) override;
		void SetDecel(const float tweeker, const float radius);

	private:

		float controlDecelTweker;
		float controlDecelRadius;

	};
}