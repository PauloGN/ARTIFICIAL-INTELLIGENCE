#include "RaveCharacter.h"

RaveCharacter::RaveCharacter()
{
	
}

RaveCharacter::~RaveCharacter()
{
}

void RaveCharacter::Render()
{
	//Rendering
	X::DrawSprite(charSprite, charPosition);
}

void RaveCharacter::CleanUp()
{
	
}

void RaveCharacter::Initialize()
{
	charSprite = X::LoadTexture("R_Walk_05.png");
	charPosition = { 300.f, 400.f };
	charDir = { 1.f, 1.f };
}

void RaveCharacter::Update(const float& deltaTime)
{
}

void RaveCharacter::Movement(const float& deltaTime)
{
	if (X::IsKeyDown(X::Keys::W))
	{
		charPosition.y -= deltaTime + charDir.y;
	}
	if (X::IsKeyDown(X::Keys::A))
	{
		charPosition.x -= deltaTime + charDir.x;
	}
	if (X::IsKeyDown(X::Keys::S))
	{
		charPosition.y += deltaTime + charDir.y;
	}
	if (X::IsKeyDown(X::Keys::D))
	{
		charPosition.x += deltaTime + charDir.x;
	}
}

void RaveCharacter::CharAutoMove(const float& deltaTime)
{
	charPosition.x += (deltaTime * charDir.x * speed);
	charPosition.y += (deltaTime * charDir.y * speed);
}

void RaveCharacter::ScreenBoundsControl(bool bManualControl)
{
	//Screen Bounds
	const uint32_t screenWidth = X::GetScreenWidth();
	const uint32_t screenHeight = X::GetScreenHeight();
	const float halfSpriteWidth = X::GetSpriteWidth(charSprite) * .5f;;
	const float halfSpriteHeight = X::GetSpriteHeight(charSprite) * .5f;

	//Right side of screen
	if (charPosition.x > screenWidth - halfSpriteWidth)
	{
		charPosition.x = screenWidth - halfSpriteWidth;
		if (!bManualControl)
		{
			charDir.x *= -1;
		}
	}

	//Left side of screen
	if (charPosition.x < halfSpriteWidth)
	{
		charPosition.x = halfSpriteWidth;
		if (!bManualControl)
		{
			charDir.x *= -1;
		}
	}

	//Top side of screen
	if (charPosition.y > screenHeight - halfSpriteHeight)
	{
		charPosition.y = screenHeight - halfSpriteHeight;
		if (!bManualControl)
		{
			charDir.y *= -1;
		}
	}

	//Bottom side of screen
	if (charPosition.y < halfSpriteHeight)
	{
		charPosition.y = halfSpriteHeight;
		if (!bManualControl)
		{
			charDir.y *= -1;
		}
	}
}