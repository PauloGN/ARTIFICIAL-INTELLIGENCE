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

void RaveCharacter::Initialize(const char* path, const float speed)
{
	charSprite = X::LoadTexture(path);
	this->speed = speed;
	charPosition = { 300.f, 400.f };
	charDir = { 1.f, 1.f };
	autoCharDir = { 1.f, 1.f };

	screenWidth = X::GetScreenWidth();
	screenHeight = X::GetScreenHeight();
	halfSpriteWidth = X::GetSpriteWidth(charSprite) * .5f;
	halfSpriteHeight = X::GetSpriteHeight(charSprite) * .5f;
}

void RaveCharacter::Update(const float& deltaTime)
{
	// Movement
	if (bManualControl)
	{
		Movement(deltaTime);
	}
	else
	{
		CharAutoMove(deltaTime);
	}

	ScreenBoundsControl();
}

void RaveCharacter::Movement(const float& deltaTime)
{
	if (X::IsKeyDown(X::Keys::W))
	{
		charPosition.y -= deltaTime * charDir.y * speed;
	}								
	if (X::IsKeyDown(X::Keys::A))	
	{								
		charPosition.x -= deltaTime * charDir.x * speed;
	}								
	if (X::IsKeyDown(X::Keys::S))	
	{								
		charPosition.y += deltaTime * charDir.y * speed;
	}								
	if (X::IsKeyDown(X::Keys::D))	
	{								
		charPosition.x += deltaTime * charDir.x * speed;
	}
}

void RaveCharacter::CharAutoMove(const float& deltaTime)
{
	charPosition += autoCharDir * deltaTime * speed;
}

void RaveCharacter::ScreenBoundsControl()
{
	//Right side of screen
	if (charPosition.x > screenWidth - halfSpriteWidth)
	{
		charPosition.x = screenWidth - halfSpriteWidth;
		if (!bManualControl)
		{
			autoCharDir.x *= -1;
		}
	}

	//Left side of screen
	if (charPosition.x < halfSpriteWidth)
	{
		charPosition.x = halfSpriteWidth;
		if (!bManualControl)
		{
			autoCharDir.x *= -1;
		}
	}

	//Bottom side of screen
	if (charPosition.y > screenHeight - halfSpriteHeight)
	{
		charPosition.y = screenHeight - halfSpriteHeight;
		if (!bManualControl)
		{
			autoCharDir.y *= -1;
		}
	}

	//Top side of screen
	if (charPosition.y < halfSpriteHeight)
	{
		charPosition.y = halfSpriteHeight;
		if (!bManualControl)
		{
			autoCharDir.y *= -1;
		}
	}
}

void RaveCharacter::SetbManualControl(const bool cond)
{
	bManualControl = cond;
}