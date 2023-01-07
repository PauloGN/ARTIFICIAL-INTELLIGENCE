#pragma once
#include<REngine.h>
#include<iostream>


class Character
{

public:

	//Singleton Functions
	static void StaticInitialize();
	static void StaticTerminate();
	static Character& Get();


	void Load(const float initialSpeed);
	void Unload();
	void Update(float deltaTime);
	void Render();

	Character();


private:

	//Sprites
	Rectangle mRecSprite;
	Texture2D mCharTexture;
	
	float mMoveSpeed = 0.0f;
	REng::Math::Vector2 mPlayerPos;

	//Animation
	bool bIsMoving;
	float currentTime;
	int currentSprite;

private:

	void PlayerMovement(float deltaTime);
	void Idle(float deltaTime);
	void UpdateRecSprite(bool isMoving, const float recX, const float recY);

};
