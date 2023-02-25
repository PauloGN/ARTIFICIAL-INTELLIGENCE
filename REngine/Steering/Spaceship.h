#pragma once

#include "AI.h"
#include "REngine.h"


class Spaceship : public AI::Agent
{
public:
	Spaceship(AI::AIWorld& world);

	void Load();
	void Unload();
	void Update(float deltaTime);
	void Render();

private:

	std::array<Texture2D, 16> mTextures;

};
