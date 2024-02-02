#pragma once
#include "CharacterBase.h"
class Ninja : public CharacterBase
{

public:

	~Ninja();
	void Initialize();
	void Cleanup();
	void Update(const float& _dt);
	void Move(const float& deltaTime);
};

