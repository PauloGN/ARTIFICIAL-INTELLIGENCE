#include "GameManager.h"
#include "Bullet.h"
#include "Fighter.h"
//#include "ImGui/Inc/imgui.h"

Fighter ft;
constexpr unsigned maxBullets = 20;
unsigned index = 0;
Bullet Bullets[maxBullets];

void GameManager::Initialize()
{
	ft.Load("SpaceshipSprites/redfighter.png", 500.0f);

	for (auto& bullet : Bullets)
	{
		bullet.Load("SpaceshipSprites/bullet.png", 1800);
	}
}

void GameManager::Render()
{
	ft.Render();
}

void GameManager::Update(const float& deltaTime)
{
	ft.Update(deltaTime);

	for (auto& bullet : Bullets)
	{
		bullet.Update(deltaTime);
		bullet.Render();
	}

	//Check keyboard and joystick input
	if (X::IsKeyPressed(X::Keys::P) || X::IsAPressed(0))
	{
		if(!Bullets[index % maxBullets].IsActive())
		{
			const X::Math::Vector2& position = ft.GetPosition();

			Bullets[index++ % maxBullets].Fire(position, { .3f, -1 });
			Bullets[index++ % maxBullets].Fire(position, { 0, -1 });
			Bullets[index++ % maxBullets].Fire(position, {-.3f, -1});
		}
	}
}

void GameManager::CleanUp()
{

}

void GameManager::DebugUI()
{
	//ImGui::ShowDemoWindow();
}
