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

		//{0.0f, 1.0f}
		//target ahead the local position
		AIMath::Vector2 mLocalWanderTarget = AIMath::Vector2::YAxis();

		//radius surrounding the player
		float mWanderRadius = 5.0f;
		//how far is the center of the center from the local position
		float mWanderDistance = 10.0f;
		float mWanderJitter = 1.0f;

	};
}