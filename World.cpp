#include "World.h"
#include <random>

World::World(sf::Vector2u windowSize)
{
	_blockSize = 16;

	_windowSize = windowSize;

	respawnApple();

	_apple.setFillColor(sf::Color::Red);
	_apple.setRadius(_blockSize / 2);


	//that loop sets the color of the each wall
	//and places them on the world map
	for (int i = 0; i < 4; i++)
	{
		_bounds[i].setFillColor(sf::Color(245, 130, 193));

		//if i is even, then it sets it to the window width(X)
		//if i is odd, then it sets it to the window height(Y)
		if (!((i + 1) % 2))
			_bounds[i].setSize(sf::Vector2f(_windowSize.x,
				_blockSize));
		else
			_bounds[i].setSize(sf::Vector2f(_blockSize,
				_windowSize.y));

		//for two walls it places it to the left top corner,
		//that is up and left walls
		//and for another walls it places the walls to the
		//right bottom corner
		if (i < 2)
			_bounds[i].setPosition(0, 0);
		else
		{
			_bounds[i].setOrigin(_bounds[i].getSize());
			_bounds[i].setPosition(sf::Vector2f(_windowSize));
		}
	}
}

World::~World() {  }

void World::respawnApple()
{
	//grid spaces for apple spawn
	//+1 - the lowes possible number
	int max_X = (_windowSize.x / _blockSize) - 2;
	int max_Y = (_windowSize.y / _blockSize) - 2;

	//random spawn apple
	_appleCoords = sf::Vector2i(std::rand() % max_X + 1,
		std::rand() % max_Y + 1);

	_apple.setPosition(_appleCoords.x * _blockSize,
		_appleCoords.y * _blockSize);
}

void World::update(Snake& player)
{
	//if player ate the apple respawn new and extend the snake
	if (player.getPosition() == _appleCoords)
	{
		player.extend();
		player.increaseScore();
		respawnApple();
	}

	int grid_x = _windowSize.x / _blockSize;
	int grid_y = _windowSize.y / _blockSize;

	//check collision with boundaries
	//if collide, lose game
	if (player.getPosition().x <= 0 ||
		player.getPosition().y <= 0 ||
		player.getPosition().x >= grid_x - 1 ||
		player.getPosition().y >= grid_y - 1)
	{
		player.lose();
	}
}

int World::getBlockSize() { return _blockSize; }

void World::render(sf::RenderWindow& window)
{
	for (int i = 0; i < 4; i++)
		window.draw(_bounds[i]);

	window.draw(_apple);
}