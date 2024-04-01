#include "Fighter.h"

void Fighter::Load(const char* assetName, const float moveSpeed)
{
	mTextureId = X::LoadTexture(assetName);
	mMoveSpeed = moveSpeed;

	//se initial position to the middle o screen
	float x = static_cast<float>(X::GetScreenWidth())  * 0.5f;
	float y = static_cast<float>(X::GetScreenHeight()) * 0.5f;
	mPosition = {x, y};
}

void Fighter::Unload()
{
	mTextureId = 0;
	mMoveSpeed = 0.0f;
}

void Fighter::Update(const float& deltaTime)
{
	Move(deltaTime);
}

void Fighter::Render()
{
	X::DrawSprite(mTextureId, mPosition);
}

void Fighter::Move(const float& deltaTime)
{
	//Move right
	if (X::IsKeyDown(X::Keys::D) || X::IsLeftThumbStickRight())
	{
		mDirection.x = 1.0f;
		mPosition.x += deltaTime * mMoveSpeed * mDirection.x;
	}

	//Move Left
	if (X::IsKeyDown(X::Keys::A) || X::IsLeftThumbStickLeft())
	{
		mDirection.x = -1.0f;
		mPosition.x += deltaTime * mMoveSpeed * mDirection.x;
	}

	//Move Up
	if (X::IsKeyDown(X::Keys::W) || X::IsLeftThumbStickUp())
	{
		mDirection.y = -1.0f;
		mPosition.y += deltaTime * mMoveSpeed * mDirection.y;
	}

	//Move Down
	if (X::IsKeyDown(X::Keys::S) || X::IsLeftThumbStickDown())
	{
		mDirection.y = 1.0f;
		mPosition.y += deltaTime * mMoveSpeed * mDirection.y;
	}
}
