#pragma once
#include <GLFW/glfw3.h>

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

	float getLastFrameTime() { return m_lastFrameTime; }
	void setLastRestartTimeToCurrentTime() { m_lastRestartTime = float(glfwGetTime()); }

private:
	float m_lastFrameTime = 0.0f;
	float m_lastRestartTime = 0.0f;
};