#pragma once
#include "SteeringBehavior.h"


namespace AI
{
	class EvadeBehavior : public SteeringBehavior
	{
	public:

		virtual std::pair<float, float> Calculate(Agent& agent) override;

		void SetPredictionPoint(const float prediction);

	private:

		float predictionPoint = 0.0f;
	};
}