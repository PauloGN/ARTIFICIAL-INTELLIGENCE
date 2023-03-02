#pragma once

//https://www.red3d.com/cwr/steer/

namespace AI
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

	public:



		//HelperFunction
		float SSqrt(float value) { return sqrtf(value); }
		float SMagnitudeSqr(const std::pair<float, float>& v) { return (v.first * v.first) + (v.second * v.second); }
		float SMagnitude(const std::pair<float, float>& v) { return SSqrt(SMagnitudeSqr(v)); }


	private:

		bool mActive = false;
		bool mDebug = false;
	};
}