#include "Precompiled.h"
#include "Entity.h"
#include "AIWorld.h"

AI::Entity::Entity(AIWorld& world, uint32_t typeId)
	:world (world), mUniqueID(static_cast<uint64_t>(typeId) << 32 | world.GetNextID())
{
	world.RegisterEntity(this);	
}

AI::Entity::~Entity()
{
	world.UnRegisterEntity(this);
}


/*

//63[	typeID	]32---31[	NextID	]0

*/