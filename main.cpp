#include "game.h"

int main()
{
	std::srand(time(nullptr));

	Game game;


	while (!game.GetWindow()->isClosed())
	{
		game.HandleInput();
		game.Update();
		game.Render();
		game.RestartClock();
	}
	return 1;
}