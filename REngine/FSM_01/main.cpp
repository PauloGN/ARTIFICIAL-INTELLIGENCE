#include <REngine.h>
#include <AI.h>
#include "Ninja.h"

//#include "Zombie.h"
//#include "Brain.h"
//
namespace
{
	std::unique_ptr<AI::AIWorld> world;
	std::unique_ptr<Ninja> ninja;
	//std::vector<std::unique_ptr<Brain>> brains;

	const int maxNumberOfBrains = 10;
	int currentNumberOfBrains = 10;
}


void GameInit()
{
	world = std::make_unique<AI::AIWorld>();
	ninja = std::make_unique<Ninja>(*world.get());
	ninja->Load("CharHero4.1.png", 100.f, 64, 64, 0, 5, 7, 6, 4, 44, 8, 8, 2);

	//for (int i = 0; i < maxNumberOfBrains; ++i)
	//{
	//	auto& newBrain = brains.emplace_back(std::make_unique<Brain>(*world.get()));
	//	newBrain->Load();
	//	newBrain->position = { EMath::RandomFloat(100.0f, 1600.0f), EMath::RandomFloat(100.0f, 500.0f) };
	//}
}

bool GameUpdate()
{
	float deltaTime = GetFrameTime();
	ninja->Update(deltaTime);
	ninja->Render();


	//for (auto iter = brains.begin(); iter != brains.end();)
	//{
	//	Brain* brain = iter->get();
	//	if (brain->IsConsumed())
	//	{
	//		iter = brains.erase(iter);
	//		world->UnregisterEntity(brain);
	//	}
	//	else
	//	{
	//		iter++;
	//	}
	//}

	//for (auto& brain : brains)
	//{
	//	brain->Update(deltaTime);
	//	brain->Render();
	//}

	bool isStopped = IsKeyPressed(KeyboardKey::KEY_ESCAPE);
	return isStopped;
}

void GameCleanup()
{

}

void RenderDebugUI()
{}

int main()
{
	REng::Start("FSM");
	GameInit();
	REng::Run(GameUpdate, RenderDebugUI);
	GameCleanup();
	REng::Stop();
	return 0;
}
