#pragma once

#include <SFML/Graphics.hpp>
#include <vector>


//every piece of the snake on the world grid
struct SnakeSegment
{
	SnakeSegment(int x, int y) : position(x, y)
	{

	}
		sf::Vector2i position;
};

using SnakeContainer = std::vector<SnakeSegment>;

enum class Direction
{
	Up, Down, Left, Right, None
};

class Snake
{
public:
	Snake(int graphicsSize);
	~Snake();

	Direction getPhysicalDirection();
	bool isAlive();
	int getSpeed();
	int getScore();
	int getLives();
	sf::Vector2i getPosition();

	void setDirection(Direction dir);
	void increaseScore();
	void lose();                               //player has lost
	void switchAlive();
	void extend();                             //extend the body   
	void newGame();                            //new game
	void move();
	void update();                              
	void cut(int segmentsCount);
	void render(sf::RenderWindow& window);
private:
	void checkCollision();

	SnakeContainer _snake;                     //snake body
	int _graphicsSize;                         //size of the graphics
	Direction _dir;
	bool _isDead;
	int _speed;
	int _lives;
	int _score;
	sf::RectangleShape _body;
};