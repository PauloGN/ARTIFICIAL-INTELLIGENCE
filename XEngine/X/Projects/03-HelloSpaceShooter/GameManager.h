#pragma once

class GameManager
{
private:

public:

	void Initialize();
	void Render();
	void Update(const float& deltaTime);
	void CleanUp();
	void DebugUI();
};
