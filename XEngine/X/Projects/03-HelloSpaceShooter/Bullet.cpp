#include "Bullet.h"

void Bullet::Load(const char* assetName, const float moveSpeed)
{
	mTextureId = X::LoadTexture(assetName);
	mMoveSpeed = moveSpeed;
	bulletSound = X::LoadSound("shootlaser1.wav");
	mSpriteHeight = static_cast<float>(X::GetSpriteHeight(mTextureId));
	mSpriteWidth =  static_cast<float>(X::GetSpriteWidth(mTextureId));
	mDirection = {0, -1};
}

void Bullet::Unload()
{
	//empty
}

void Bullet::Update(const float& deltaTime)
{
	if(mActive)
	{
		Move(deltaTime);
		const float screemWidth = static_cast<float>(X::GetScreenWidth());
		const float screenHeight = static_cast<float>(X::GetScreenHeight());

		if (mPosition.x > screemWidth
			|| mPosition.x < 0
			|| mPosition.y > screenHeight
			|| mPosition.y < 0)
		{
			Deactivate();
		}
	}
}

void Bullet::Render()
{
	if(mActive)
	{
		X::DrawSprite(mTextureId, mPosition);
	}
}

void Bullet::Fire(const X::Math::Vector2& pos, const X::Math::Vector2& dir)
{
	mPosition = pos;
	mActive = true;
	mDirection = dir;
}

void Bullet::Deactivate()
{
	mActive = false;
}

void Bullet::Move(const float& deltaTime)
{
	mPosition += Normalize(mDirection) * deltaTime * mMoveSpeed;
}
