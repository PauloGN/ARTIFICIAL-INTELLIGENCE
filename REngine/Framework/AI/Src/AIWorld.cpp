#include "Precompiled.h"
#include "AIWorld.h"

void AI::AIWorld::RegisterEntity(Entity* entity)
{
	assert((std::find(mEntities.begin(), mEntities.end(), entity)) == mEntities.end() && "Entity already Registered");

	mEntities.push_back(entity);
}

void AI::AIWorld::UnRegisterEntity(Entity * entity)
{
	auto iter = std::find(mEntities.begin(), mEntities.end(), entity);

	if (iter != mEntities.end())
	{
		//Constant time removal
		std::iter_swap(iter, mEntities.end() - 1);
		mEntities.pop_back();
	}
}
