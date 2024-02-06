#include "Ninja.h"
#include "AnimationComponent.h"
#include "Animation.h"

Ninja::~Ninja()
{
	Cleanup();
}

void Ninja::Initialize(const X::Math::Vector2 position)
{
	animationManager->LoadAnimation("Config/Animation.ini");
	
	baseRect.min.x = 0;
	baseRect.min.y = 0;
	baseRect.max.x = 64;
	baseRect.max.y = 64;

	speed = 200;
	this->pos = position;
}

void Ninja::Cleanup()
{
	
}

void Ninja::Update(const float& _dt)
{
	animationManager->UpdateAnimation(_dt);
	Move(_dt);
}

void Ninja::Move(const float& deltaTime)
{
	
	// Store the initial position for later comparison
	const X::Math::Vector2 initialPos = pos;

	//Move right
	if (X::IsKeyDown(X::Keys::D))
	{
		animationManager->ChangeAnimation("Right");
		dir.x = 1.0f;
		pos.x += deltaTime * speed * dir.x;
	}

	//Move Left
	if (X::IsKeyDown(X::Keys::A))
	{
		animationManager->ChangeAnimation("Left");
		dir.x = -1.0f;
		pos.x += deltaTime * speed * dir.x;
	}

	//Move Up
	if (X::IsKeyDown(X::Keys::W))
	{
		animationManager->ChangeAnimation("Up");
		dir.y = -1.0f;
		pos.y += deltaTime * speed * dir.y;
	}

	//Move Down
	if (X::IsKeyDown(X::Keys::S))
	{
		animationManager->ChangeAnimation("Down");
		dir.y = 1.0f;
		pos.y += deltaTime * speed * dir.y;
	}

	// Check if the position has changed, indicating movement
	if (initialPos == pos)
	{
		// Call Idle animation or perform any other idle-related tasks
		animationManager->ChangeAnimation("Idle");
	}
}