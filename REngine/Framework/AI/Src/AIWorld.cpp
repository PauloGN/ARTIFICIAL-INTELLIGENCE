#include "Precompiled.h"
#include "AIWorld.h"

#include "Entity.h"


namespace
{

	const float sCellSize = 100.0f;

}


void AI::AIWorld::RegisterEntity(Entity* entity)
{
	assert((std::find(mEntities.begin(), mEntities.end(), entity)) == mEntities.end() && "Entity already Registered");

	mEntities.push_back(entity);
}

void AI::AIWorld::UnregisterEntity(Entity * entity)
{
	auto iter = std::find(mEntities.begin(), mEntities.end(), entity);

	if (iter != mEntities.end())
	{
		//Constant time removal
		std::iter_swap(iter, mEntities.end() - 1);
		mEntities.pop_back();
	}
}

std::vector<AI::Entity*> AI::AIWorld::GetAllEntitiesOfType(uint32_t typeID)
{
	std::vector<Entity*> entities;
	for (auto entity : mEntities)
	{
		if (entity->GetTypeID() == typeID)
		{
			entities.push_back(entity);
		}
	}

	return entities;
}

