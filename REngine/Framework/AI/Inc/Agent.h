#pragma once
#include "Entity.h"
#include <AIMath.h>

namespace AI
{
	class Agent;
	using AgentPtrs = std::vector<Agent*>;

	class Agent : public Entity
	{
	public:
		Agent(AIWorld& world, uint32_t typeId);
		~Agent() override = default;

		void SetTarget(Agent* otherA);

		AIMath::Matrix3 GetWorldTransform() const;

		Agent* otherAgent = nullptr;
		float velovityX = 0;
		float velovityY = 0;
		
		float DestinationX = 0;
		float DestinationY = 0;

		float maxSpeed = 100.0f;
		float mass = 1.0f;

		//Group behavior
		std::vector<Agent*> agentNeighbors;
		float NeighborRadius = 150.0f;

		//45min

	};
}