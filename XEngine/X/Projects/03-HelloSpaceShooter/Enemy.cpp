#include "Enemy.h"

void Enemy::Load()
{
	mTexture = X::LoadTexture("SpaceshipSprites/spaceship_09.png");
	mHalfSpriteWidth = static_cast<float>(X::GetSpriteWidth(mTexture)) * .5f;
	mDelay = X::RandomFloat(1.0f, 3.0f);
}

void Enemy::Unload()
{

}

void Enemy::Update(const float& deltaTime)
{
	if (!mActive) return;

	mPosition += mVelocity * deltaTime;

	mDelay -= deltaTime;
	if(mDelay <= 0.0f)
	{
		mVelocity.x *= -1.0f;
		//Reset Delay
		mDelay = X::RandomFloat(1.0f, 3.0f);
	}
}

void Enemy::Render()
{
	if(mActive)
	{
		X::DrawSprite(mTexture, mPosition);
	}
}

void Enemy::Spawn(const X::Math::Vector2& position)
{
	mPosition = position;
	mVelocity = {200.0f, 200.0f};
	mActive = true;
}

void Enemy::Kill()
{
	mActive = false;
}

X::Math::Circle Enemy::GetBoundingCircle() const
{
	return { mPosition, mHalfSpriteWidth };
}
