#pragma once

#include <SFML/Graphics.hpp>
#include "Snake.h"

class World
{
public:
	World(sf::Vector2u windowSize);
	~World();

	int getBlockSize();

	void respawnApple();

	void update(Snake& player);
	void render(sf::RenderWindow& window);
private:
	sf::Vector2u _windowSize;
	sf::Vector2i _appleCoords;

	int _blockSize;

	sf::CircleShape _apple;
	sf::RectangleShape _bounds[4];
};