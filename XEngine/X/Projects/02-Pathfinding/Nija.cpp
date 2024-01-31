#include "Ninja.h"
#include "AnimationComponent.h"
#include "Animation.h"

Ninja::~Ninja()
{
	Cleanup();
}

void Ninja::Initialize()
{
	spriteSheet = X::LoadTexture("Ninja.png");
	spriteOffset.x = 64;
	spriteOffset.y = 64;
	
	baseRect.min.x = 0;
	baseRect.min.y = 0;
	baseRect.max.x = 64;
	baseRect.max.y = 64;

	Animation* idle = new Animation(8, .2f, 0);
	Animation* up = new Animation(8, .1f, 6);
	animationManager->AddAnimation("Idle", idle);
	animationManager->AddAnimation("Up", up);

}

void Ninja::Cleanup()
{
	animationManager->CleanUp();
}

void Ninja::Update(const float& _dt)
{
	
	animationManager->UpdateAnimation(_dt);

	if (X::IsKeyPressed(X::Keys::W))
	{
		animationManager->ChangeAnimation("Up");
	}

	if (X::IsKeyPressed(X::Keys::SPACE))
	{
		animationManager->ChangeAnimation("Idle");
	}
}
