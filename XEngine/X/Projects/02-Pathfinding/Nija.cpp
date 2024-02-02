#include "Ninja.h"
#include "AnimationComponent.h"
#include "Animation.h"

Ninja::~Ninja()
{
	Cleanup();
}

void Ninja::Initialize()
{
	animationManager->LoadAnimation("Config/Animation.ini");
	
	baseRect.min.x = 0;
	baseRect.min.y = 0;
	baseRect.max.x = 64;
	baseRect.max.y = 64;

	speed = 200;
}

void Ninja::Cleanup()
{
	animationManager->CleanUp();
}

void Ninja::Update(const float& _dt)
{
	Move(_dt);
	animationManager->UpdateAnimation(_dt);
}

void Ninja::Move(const float& deltaTime)
{
	
	// Store the initial position for later comparison
	X::Math::Vector2 initialPos = pos;

	//Move right
	if (X::IsKeyDown(X::Keys::D))
	{
		dir.x = 1.0f;
		pos.x += deltaTime * speed * dir.x;
		animationManager->ChangeAnimation("Right");
	}

	//Move Left
	if (X::IsKeyDown(X::Keys::A))
	{
		dir.x = -1.0f;
		pos.x += deltaTime * speed * dir.x;
		animationManager->ChangeAnimation("Left");
	}

	//Move Up
	if (X::IsKeyDown(X::Keys::W))
	{
		dir.y = -1.0f;
		pos.y += deltaTime * speed * dir.y;
		animationManager->ChangeAnimation("Up");
	}

	//Move Down
	if (X::IsKeyDown(X::Keys::S))
	{
		dir.y = 1.0f;
		pos.y += deltaTime * speed * dir.y;
		animationManager->ChangeAnimation("Down");
	}

	// Check if the position has changed, indicating movement
	if (initialPos == pos)
	{
		// Call Idle animation or perform any other idle-related tasks
		animationManager->ChangeAnimation("Idle");
	}
}