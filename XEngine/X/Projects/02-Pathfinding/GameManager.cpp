#include "GameManager.h"
#include "Ninja.h"

Ninja nj;

void GameManager::Initialize()
{
	X::TileMapCreator::StaticInitialize();
	X::TileMapCreator::Get().Load("Config/Level_A.txt", "Config/TileSet.txt" );

	nj.Initialize({200.0f, 150.0f});
}

void GameManager::Render()
{
	X::TileMapCreator::Get().Render();
	nj.Render();
}

bool GameManager::Update(const float& deltaTime)
{
	X::TileMapCreator::Get().Update(deltaTime);
	nj.Update(deltaTime);

	//Exit condition
	const bool bExit = X::IsKeyPressed(X::Keys::ESCAPE);

	if(X::IsKeyPressed(X::Keys::P))
	{
		X::TileMapCreator::Get().Unload();
	}

	return bExit;
}

void GameManager::CleanUp()
{
	nj.Cleanup();
	X::TileMapCreator::Get().Unload();
	X::TileMapCreator::StaticTerminate();
}

void GameManager::DebugUI()
{
	ImGui::ShowDemoWindow();
}
