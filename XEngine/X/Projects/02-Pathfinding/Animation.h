#pragma once

class CharacterBase;

class Animation
{
public:

	Animation(const int _frames, const float _animFrameRate, const float _YFramePos);

	//members
	int numOfFrames;
	float yFrameRow;
	float animFrameRate;
};