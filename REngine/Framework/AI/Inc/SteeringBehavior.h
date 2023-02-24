#pragma once

namespace
{
	class Agent;
	class SteeringBehavior
	{
	public:
		
		virtual ~SteeringBehavior() = default;
		
		virtual std::pair<float, float> Calculate(Agent& agent) = 0;
		
		//get and set
		void SetActive(bool active) { mActive = active; }
		bool IsActive() const { return mActive; }

		void ShowDebug(bool debug) { mDebug = debug; }
		bool IsDebug() const { return mDebug; }


	private:

		bool mActive = false;
		bool mDebug = false;
	};
}