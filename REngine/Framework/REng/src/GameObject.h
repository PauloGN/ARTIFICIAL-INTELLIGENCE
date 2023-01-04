#pragma once

class GameObject
{
public:
	virtual void Initialize() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Terminate() = 0;
};