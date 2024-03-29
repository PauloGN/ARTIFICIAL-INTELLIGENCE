#include "Bullet.h"

void Bullet::Load(const char* assetName, const float moveSpeed)
{
	mTextureId = X::LoadTexture(assetName);
	mMoveSpeed = moveSpeed;

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
		const float gScreemWidth = static_cast<float>(X::GetScreenWidth());
		const float gScreenHeight = static_cast<float>(X::GetScreenHeight());

		if (mPosition.x > gScreemWidth
			|| mPosition.x < 0
			|| mPosition.y > gScreenHeight
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
	mPosition += mDirection * deltaTime * mMoveSpeed;
}
