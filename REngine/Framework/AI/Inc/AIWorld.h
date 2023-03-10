#pragma once

/*

//Collision Geometry
Ai can be aware of the boundaries of the environment

//Pathing ok done

//Events listeners that will respond to events thrown by functions or side effects it can change state machine (event dispatcher)

//AI Module
perception (hear, see, felling)

//Decision

FSM
Bevavior tree
fuzzy logic
Decision Module

*/

#include "AI.h"

namespace AI
{
	class Entity;


	using EntityPtrs = std::vector<Entity*>;

	class AIWorld
	{
	public:
		
		//we are goint to register the agent in AI World each one is going to have its own ID
		void RegisterEntity(Entity* entity);
		void UnregisterEntity(Entity* entity);

		std::vector<Entity*> GetAllEntitiesOfType(uint32_t typeID);

		uint32_t GetNextID() const
		{ 
			assert(mNextID < UINT32_MAX && "AIWorld run out of IDs");
			return mNextID++;
		}

	private:

		EntityPtrs mEntities;
		mutable uint32_t mNextID = 0;
		//PartitionGrid<Entity> mGrid;

	};
}