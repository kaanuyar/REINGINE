#include "Application.h"
#include <iostream>

Application::Application()
	: m_window(800, 450, std::string("Kaimon")), m_game(m_window)
{
}

void Application::runLoop()
{
	while (!m_window.isWindowShouldClose())
	{
		float deltaTime = m_timer.getDeltaTime(1.0f/60.0f);
		if (deltaTime > 0.2f)	deltaTime = 0.2f;
		m_timer.countDeltaTimeTowardsFPS(deltaTime);

		if (m_timer.returnEverySecond(deltaTime))
			std::cout << "FPS: " << m_timer.getFPS() << std::endl;

		if (!m_window.isWindowIconified())
			m_game.update(deltaTime);

		m_window.update();
	}
}