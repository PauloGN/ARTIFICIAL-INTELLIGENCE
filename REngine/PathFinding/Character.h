#pragma once
#include<REngine.h>
#include<iostream>


class Character
{

public:
	void Load(const float initialSpeed);
	void Unload();
	void Update(float deltaTime);
	void Render();

	Character();


private:

	Rectangle mRecSprite;
	float mMoveSpeed = 0.0f;
	Texture2D mCharTexture;
	REng::Math::Vector2 mPlayerPos;
	bool bIsMoving;

	//Animation
	float currentTime;
	int currentSprite;

private:

	void PlayerMovement(float deltaTime);
	void Idle(float deltaTime);
	void UpdateRecSprite(bool isMoving, const float recX, const float recY);

};
