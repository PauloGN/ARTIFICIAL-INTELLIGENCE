#include "Precompiled.h"
#include "Agent.h"

using namespace AI;
using namespace AI::AIMath;
void AI::Agent::SetTarget(Agent* otherA)
{
	otherAgent = otherA;
}

AIMath::Matrix3 AI::Agent::GetWorldTransform() const
{
	//headind to...
	const AIMath::Vector2 hForawdVector = {headingX, headingY};
	//Perpendicular RH of (x,y) is (y, -x)
	const AIMath::Vector2 sideVector = AIMath::PerpendicularRH(hForawdVector);
	//position
	const AIMath::Vector2 displacement = {posX, posY};

	return AIMath::Matrix3(
		sideVector.x,		sideVector.y,		0.0f,
		hForawdVector.x,	hForawdVector.y,	0.0f,
		displacement.x,		displacement.y,		1.0f
	);
}

Agent::Agent(AIWorld& world, uint32_t typeID)
	: Entity(world, typeID)
{

	velovityX = 0;
	velovityY = 0;

	DestinationX = 0;
	DestinationY = 0;
}