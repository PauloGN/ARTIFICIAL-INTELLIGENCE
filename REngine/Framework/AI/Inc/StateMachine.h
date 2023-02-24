#pragma once

#include "State.h"

namespace AI
{
	template<class AgentType>
	class StateMachine final
	{
	public:
		using StateType = State<AgentType>;

		StateMachine(AgentType& agent)
			:mAgent(agent)
		{}

		template<class NewStateType>
		void AddState()
		{
			static_assert(std::is_base_of_v<StateType, NewStateType>, "StateMachine -- Can only add state for agent Type.");
			mStates.push_back(std::make_unique<NewStateType>());
		}

		void Update(float deltaTime)
		{
			assert(mCurrentState != nullptr, "StateMachine --- Current State is null!");
			mCurrentState->Update(mAgent, deltaTime);
		}

		void ChangeState(int index)
		{
			assert(index >= 0 && index < mStates.size(), "StateMachine --- Invalid index %i, state count = %zu", index, mStates.size());
			if (mCurrentState)
				mCurrentState->Exit(mAgent);
			mCurrentState = mStates[index].get();
			mCurrentState->Enter(mAgent);
		}

	private:
		AgentType& mAgent;
		StateType* mCurrentState = nullptr;
		std::vector<std::unique_ptr<StateType>> mStates;
	};
}