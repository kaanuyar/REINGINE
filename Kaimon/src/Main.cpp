#include "Window.h"
#include "Timer.h"
#include "Game.h"

int main()
{
	Window window(800, 450, std::string("Kaimon"));
	Game game(window);
	Timer timer;
	float systemDeltaTime = 0.0f;

	while (!window.isWindowShouldClose())
	{
		float deltaTime = timer.getDeltaTime() - systemDeltaTime;

		if(!window.isWindowIconified())
			game.update(deltaTime);

		systemDeltaTime = window.update();
	}

	return 0;
}