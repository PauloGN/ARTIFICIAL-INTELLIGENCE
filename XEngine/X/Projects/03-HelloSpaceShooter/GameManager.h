#pragma once
#include "Fighter.h"

class GameManager
{
private:



public:

	void Initialize();
	void Render();
	bool Update(const float& deltaTime);
	void CleanUp();
	void DebugUI();

};
