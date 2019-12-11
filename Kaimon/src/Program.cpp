#include "Program.h"

Program::Program()
	: m_window(800, 450, std::string("Kaimon")), m_game(m_window)
{
}

void Program::runLoop()
{
	while (!m_window.isWindowShouldClose())
	{
		float deltaTime = m_timer.getDeltaTime();

		if (deltaTime > 0.2f)
			deltaTime = 0.2f;

		if (!m_window.isWindowIconified())
			m_game.update(deltaTime);

		m_window.update();
	}
}