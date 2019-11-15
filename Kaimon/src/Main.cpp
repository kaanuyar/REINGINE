#include "Window.h"
#include "Timer.h"
#include "Game.h"

int main()
{
	Window window(800, 450, std::string("Kaimon"));
	Game game(window);
	Timer timer;

	while (!window.isWindowShouldClose())
	{
		float deltaTime = timer.getDeltaTime();

		game.update(deltaTime);
		window.update();
	}

	return 0;
}