#pragma once

#include "Window.h"
#include "Timer.h"
#include "Game.h"

class Application
{
public:
	Application();
	void runLoop();

private:
	Window m_window;
	Game m_game;
	Timer m_timer;
};