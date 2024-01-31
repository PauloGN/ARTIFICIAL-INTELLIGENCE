#pragma once
#include "XEngine.h"

class RaveCharacter
{
private:

	X::TextureId charSprite = 0;
	X::Math::Vector2 charPosition = 0;
	X::Math::Vector2 charDir = 0;
	X::Math::Vector2 autoCharDir = 0;
	float speed = 100.0f;
	bool bManualControl = true;

	void Movement(const float& deltaTime);
	void CharAutoMove(const float& deltaTime);
	void ScreenBoundsControl();

public:

	RaveCharacter();
	~RaveCharacter();

	void Render();
	void CleanUp();
	void Initialize();
	void Update(const float& deltaTime);

	void SetbManualControl(const bool cond);
};