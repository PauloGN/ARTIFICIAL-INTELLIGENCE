#pragma once
#include "SteeringBehavior.h"


namespace AI
{
	class AlignmentBehavior : public SteeringBehavior
	{
	public:


		virtual std::pair<float, float> Calculate(Agent& agent) override;
		void SetAlignmentForce(const float separationF);

	private:

		float percentOfForce = 1.0f;

	};
}