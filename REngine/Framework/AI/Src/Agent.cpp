#include "Precompiled.h"
#include "Agent.h"

using namespace AI;
Agent::Agent(AIWorld& world, uint32_t typeID)
	: Entity(world, typeID)
{

	velovityX = 0;
	velovityY = 0;

	DestinationX = 0;
	DestinationY = 0;
}