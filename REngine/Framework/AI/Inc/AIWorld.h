#pragma once
#include "Entity.h"

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


namespace AI
{
	class AIWorld
	{
	public:
		
		//we are goint to register the agent in AI World each one is going to have its own ID
		void RegisterEntity(Entity* entity);
		void UnRegisterEntity(Entity* entity);

		uint32_t GetNextID() 
		{ 
			assert(mNextID < UINT32_MAX && "AIWorld run out of IDs");
			return mNextID++;
		}

	private:

		std::vector<Entity*> mEntities;
		uint32_t mNextID = 0;
	};

}