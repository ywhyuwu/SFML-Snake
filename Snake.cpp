#include "Snake.h"

Snake::Snake(int graphicsSize)
{
	_graphicsSize = graphicsSize;
	_body.setSize(sf::Vector2f(_graphicsSize - 1, _graphicsSize - 1));
	newGame();
}

Snake::~Snake() {  }

void Snake::newGame()
{
	_snake.clear();

	//spawn position
	_snake.push_back(SnakeSegment(5, 7));
	_snake.push_back(SnakeSegment(5, 6));
	_snake.push_back(SnakeSegment(5, 5));

	setDirection(Direction::None);

	_speed = 15;
	_lives = 3;
	_score = 0;
	_isDead = false;
}

void Snake::setDirection(Direction dir)
{
	_dir = dir;
}

int Snake::getScore() { return _score; }
int Snake::getSpeed() { return _speed; }
int Snake::getLives() { return _lives; }
bool Snake::isAlive() { return _isDead; }
sf::Vector2i Snake::getPosition()
{
	return (!_snake.empty() ? _snake.front().position
		: sf::Vector2i(1, 1));
}

void Snake::increaseScore() { _score += 10; }
void Snake::lose() { _isDead = true; }
void Snake::switchAlive() { _isDead = !_isDead; }

void Snake::extend()
{
	if (_snake.empty())
		return;

	//the last element in the snake body
	SnakeSegment& tail_head = _snake[_snake.size() - 1];

	if (_snake.size() > 1)
	{
		//next to last element
		//it is needed for determine where the last element
		//should be placed when apple has eaten
		SnakeSegment& tail_bone = _snake[_snake.size() - 2];


		//if X are the same, then Y is changing
		if (tail_head.position.x == tail_bone.position.x)
		{
			if (tail_head.position.y > tail_bone.position.y)
			{
				_snake.push_back(SnakeSegment(tail_head.position.x,
					tail_head.position.y + 1));
			}
			else 
			{
				_snake.push_back(SnakeSegment(tail_head.position.x,
					tail_head.position.y - 1));
			}
		}
		//if Y are the same, then X is changing
		else if (tail_head.position.y == tail_bone.position.y)
		{
			if (tail_head.position.x > tail_bone.position.x)
			{	
				_snake.push_back(SnakeSegment(tail_head.position.x + 1,
					tail_head.position.y));
			}
			else
			{
				_snake.push_back(SnakeSegment(tail_head.position.x - 1,
					tail_head.position.y));
			}
		}
	}
	
	else
	{
		if (_dir == Direction::Up)
		{
			_snake.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
		}
		else if (_dir == Direction::Down)
		{
			_snake.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
		}
		else if (_dir == Direction::Left)
		{
			_snake.push_back(SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
		}
		else if (_dir == Direction::Right)
		{
			_snake.push_back(SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
		}
	}
}

void Snake::update()
{
	if (_snake.empty())
		return;

	if (_dir == Direction::None)
		return;

	move();
	checkCollision();
}

void Snake::move()
{
	//backward snake body iteration
	//it check if i!=0, cause _snake[0] is the head of the snake
	//then rely to direction it moves the head
	for (int i = _snake.size() - 1; i > 0; --i)
		_snake[i].position = _snake[i - 1].position;

	if (_dir == Direction::Up)
		--_snake[0].position.y;
	else if (_dir == Direction::Down)
		++_snake[0].position.y;
	else if (_dir == Direction::Right)
		++_snake[0].position.x;
	else if (_dir == Direction::Left)
		--_snake[0].position.x;
}

void Snake::checkCollision()
{
	//we can't eat yourself if our body is less than 4 segments
	if (_snake.size() < 5)
		return;

	SnakeSegment& head = _snake.front();

	for (auto it = _snake.begin() + 1; it != _snake.end(); ++it)
	{
		if (it->position == head.position)
		{
			int segments = _snake.end() - it;
			cut(segments);
			break;
		}
	}
}

void Snake::cut(int segmentsCount)
{
	for (int i = 0; i < segmentsCount; i++)
		_snake.pop_back();

	--_lives;
	if (!_lives)
	{
		lose();
		return;
	}
}

void Snake::render(sf::RenderWindow& window)
{
	if (_snake.empty())
		return;

	auto head = _snake.begin();

	_body.setFillColor(sf::Color::Yellow);
	_body.setPosition(static_cast<float>(head->position.x * _graphicsSize), static_cast<float>(head->position.y * _graphicsSize));
	window.draw(_body);

	_body.setFillColor(sf::Color::Green);
	for (auto itr = _snake.begin() + 1; itr != _snake.end(); ++itr)
	{
		_body.setPosition(static_cast<float>(itr->position.x * _graphicsSize), static_cast<float>(itr->position.y * _graphicsSize));
		window.draw(_body);
	}
}

Direction Snake::getPhysicalDirection() 
{
	if (_snake.size() <= 1)
		return Direction::None;

	SnakeSegment& head = _snake[0];
	SnakeSegment& neck = _snake[1];

	if (head.position.x == neck.position.x)
	{
		return(head.position.y > neck.position.y ? Direction::Down : Direction::Up);
	}
	else if (head.position.y == neck.position.y)
	{
		return(head.position.x > neck.position.x ? Direction::Right : Direction::Left);
	}

	return Direction::None;
}