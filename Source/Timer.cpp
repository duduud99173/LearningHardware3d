#include "Timer.h"

Timer::Timer()
{
	start = std::chrono::steady_clock::now();
}

float Timer::Mark()
{
	std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
	float duration = std::chrono::duration<float>(now - start).count();
	start = now;
	return duration;
}

float Timer::Peek()
{
	std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
	float duration = std::chrono::duration<float>(now - start).count();
	return duration;
}


