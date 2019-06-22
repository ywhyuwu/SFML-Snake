#pragma once

#include <SFML/Graphics.hpp>
#include "window.h"
#include "Snake.h"
#include "World.h"

class Game
{
public:
	Game();
	~Game();

	void HandleInput();
	void Update();
	void Render();
	void RestartClock();

	window* GetWindow();
	sf::Time GetDeltaTime();
private:
	window _window;

	sf::Clock _clock;
	sf::Time _deltaTime;
	
	World _world;
	Snake _player;
	sf::Font _font;
	sf::Text _scoreTable;
};