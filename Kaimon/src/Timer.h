#pragma once
#include <GLFW/glfw3.h>
#include <thread>

class Timer
{
public:
	float getDeltaTime()
	{
		float currentFrameTime = float(glfwGetTime());
		float deltaTime = currentFrameTime - m_lastFrameTime;
		m_lastFrameTime = currentFrameTime;
		return deltaTime;
	}

	float getDeltaTime(float deltaTimeLimit)
	{
		float currentFrameTime = float(glfwGetTime());
		float deltaTime = currentFrameTime - m_lastFrameTime;
		while (deltaTime < deltaTimeLimit)
		{
			std::this_thread::sleep_for(std::chrono::nanoseconds(1));
			currentFrameTime = float(glfwGetTime());
			deltaTime = currentFrameTime - m_lastFrameTime;
		}
		m_lastFrameTime = currentFrameTime;
		return deltaTime;
	}

	bool isDeltaTimeFromLastRestart(float timeLimit)
	{
		float currentFrameTime = float(glfwGetTime());
		float deltaTime = currentFrameTime - m_lastRestartTime;
		if (deltaTime > timeLimit)
		{
			m_lastRestartTime = currentFrameTime;
			return true;
		}
		return false;
	}

	void countDeltaTimeTowardsFPS(float deltaTime)
	{
		m_frameCounter++;
		m_frameCounterTime += deltaTime;
		if (m_frameCounterTime > 1.0f)
		{
			m_currentFPS = m_frameCounter;
			m_frameCounter = 0;
			m_frameCounterTime = 0.0f;
		}
	}

	bool returnEverySecond(float deltaTime)
	{
		m_everySecondTime += deltaTime;
		if (m_everySecondTime  > 1.0f)
		{
			m_everySecondTime = 0.0f;
			return true;
		}
		else
			return false;
	}

	float getLastFrameTime() { return m_lastFrameTime; }
	void setLastRestartTimeToCurrentTime() { m_lastRestartTime = float(glfwGetTime()); }

	int getFPS() { return m_currentFPS; }

private:
	float m_lastFrameTime = 0.0f;
	float m_lastRestartTime = 0.0f;

	float m_frameCounterTime = 0.0f;
	int m_frameCounter = 0;
	int m_currentFPS = 0;

	float m_everySecondTime = 0.0f;
};