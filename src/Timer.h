#pragma once

#include <functional>

#include <SFML/Graphics.hpp>

//------------------------------------------------------------------------------
class Timer
{
public:
	Timer() = default;
	Timer(const sf::Time& duration);

	void Update(const sf::Time& timestamp);		
	
	void Start();	
	void Finish();
	void Reset(bool play);	

	bool IsFinished();	
	float PercentComplete();	
	void SetDuration(const sf::Time& duration);

private:
	sf::Time mDuration;
	float mElapsedTime{ 0 };
	bool mActive{ false };	
};