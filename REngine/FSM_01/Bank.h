#pragma once
#include "AI.h"
#include "REngine.h"

class Bank : public AI::Entity
{
public:

	Bank(AI::AIWorld& world);

	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();

private:

	Texture2D mTexture;
};
