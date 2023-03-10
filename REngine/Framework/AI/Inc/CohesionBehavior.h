#pragma once
#include "SteeringBehavior.h"


namespace AI
{
	class CohesionBehavior : public SteeringBehavior
	{
	public:


		virtual std::pair<float, float> Calculate(Agent& agent) override;
		void SetCohesionForce(const float percentF);

	private:

		float percentOfForce = 1.0f;

	};
}