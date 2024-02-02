#include "GameManager.h"
#include "Ninja.h"

Ninja nj;

void GameManager::Initialize()
{
	nj.Initialize();
	nj.pos.x = 150;
	nj.pos.y = 150;
}

void GameManager::Render()
{
	nj.Render();
}

bool GameManager::Update(const float& deltaTime)
{
	nj.Update(deltaTime);

	//Exit condition
	const bool bExit = X::IsKeyPressed(X::Keys::ESCAPE);
	return bExit;
}

void GameManager::CleanUp()
{
	nj.Cleanup();
}

void GameManager::DebugUI()
{
	ImGui::ShowDemoWindow();
}
