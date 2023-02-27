#pragma once
#include "Entity.h"

namespace AI
{
	class Agent;
	using AgentPtrs = std::vector<Agent*>;

	class Agent : public Entity
	{
	public:

		Agent* otherAgent = nullptr;

		Agent(AIWorld& world, uint32_t typeId);
		~Agent() override = default;

		float velovityX = 0;
		float velovityY = 0;
		
		float DestinationX = 0;
		float DestinationY = 0;

		float maxSpeed = 100.0f;
		float mass = 1.0f;
	};
}