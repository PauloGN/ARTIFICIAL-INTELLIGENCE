#pragma once
#include "SteeringBehavior.h"
#include "AIMath.h"


namespace AI
{
	class WanderBehavior : public SteeringBehavior
	{
	public:

		virtual std::pair<float, float> Calculate(Agent& agent) override;
		void Setup(const float radius,const float distance,const float jitter);


	private:

		float mWanderRadius = 1.0f;
		float mWanderDistance = 0.0f;
		float mWanderJitter = 0.0f;

	};
}