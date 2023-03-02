#pragma once

#include "SteeringBehavior.h"

namespace AI
{
	class SteeringModule final
	{
	public:

		SteeringModule(Agent& agent);

		template<class NewBehaviorType>
		NewBehaviorType* AddBehavior()
		{
			static_assert(std::is_base_of_v<SteeringBehavior, NewBehaviorType>, "Only Behavior derived from Steering behavior are allowed.");

			auto& newBehavior = mBehaviors.emplace_back(std::make_unique<NewBehaviorType>());

			return static_cast<NewBehaviorType*>(newBehavior.get());
		}

		std::pair<float, float>Calculate();//<-vector 2 firt = X and second = Y

		SteeringBehavior* GetBehavior(int index)
		{ 
			
			if (index < 0 || index > mBehaviors.size())
			{
				return mBehaviors[0].get();
			}
			return mBehaviors[index].get();
		}


	private:
		Agent& mAgent;
		std::vector<std::unique_ptr<SteeringBehavior>> mBehaviors;
	};
}