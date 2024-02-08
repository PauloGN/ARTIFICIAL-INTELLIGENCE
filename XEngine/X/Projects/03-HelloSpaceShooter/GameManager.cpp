#include "GameManager.h"
#include "Bullet.h"
//#include "ImGui/Inc/imgui.h"

Fighter ft;
constexpr unsigned maxBullets = 20;
unsigned index = 0;
Bullet bt[maxBullets];

void GameManager::Initialize()
{
	ft.Load("SpaceshipSprites/redfighter.png", 500.0f);

	for (auto& bullet : bt)
	{
		bullet.Load("SpaceshipSprites/bullet.png", 1800);
	}
}

void GameManager::Render()
{
	ft.Render();
}

bool GameManager::Update(const float& deltaTime)
{
	ft.Update(deltaTime);

	for (auto& bullet : bt)
	{
		bullet.Update(deltaTime);
		bullet.Render();
	}

	if (X::IsKeyPressed(X::Keys::P) || X::IsAPressed(0))
	{
		if(!bt[index % maxBullets].IsActive())
		{
			const X::Math::Vector2& position = ft.GetPosition();

			bt[index++ % maxBullets].Fire(position, { .3f, -1 });
			bt[index++ % maxBullets].Fire(position, { 0, -1 });
			bt[index++ % maxBullets].Fire(position, {-.3f, -1});
		}
	}

	//Exit condition
	const bool bExit = X::IsKeyPressed(X::Keys::ESCAPE);
	return bExit;
}

void GameManager::CleanUp()
{

}

void GameManager::DebugUI()
{
	//ImGui::ShowDemoWindow();
}
