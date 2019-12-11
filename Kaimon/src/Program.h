#pragma once

#include "Window.h"
#include "Timer.h"
#include "Game.h"

class Program
{
public:
	Program();
	void runLoop();

private:
	Window m_window;
	Game m_game;
	Timer m_timer;
};