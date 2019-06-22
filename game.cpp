#include "game.h"

window* Game::GetWindow()
{
	return &_window;
}

Game::Game() :
	_window("Game"),
	_world(_window.GetWindowSize()),
	_player(_world.getBlockSize())
{	
	_font.loadFromFile("Assets/Fonts/arial.ttf");
	_scoreTable.setFont(_font);
	_scoreTable.setCharacterSize(14);
	_scoreTable.setFillColor(sf::Color::White);
	_scoreTable.setPosition(sf::Vector2f(18,18));
}

Game::~Game() {  }

void Game::HandleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
		&& _player.getPhysicalDirection() != Direction::Down) {
		_player.setDirection(Direction::Up);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
		&& _player.getPhysicalDirection() != Direction::Up) {
		_player.setDirection(Direction::Down);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
		&& _player.getPhysicalDirection() != Direction::Right) {
		_player.setDirection(Direction::Left);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
		&& _player.getPhysicalDirection() != Direction::Left) {
		_player.setDirection(Direction::Right);
	}

}

void Game::Update()
{ 
	_window.Update();

	float fps = 1.f / _player.getSpeed();

	if (_deltaTime.asSeconds() >= fps)
	{
		_player.update();
		_world.update(_player);
		_scoreTable.setString("Score: " + std::to_string(_player.getScore()) + "\n"
			+ "Lives: " + std::to_string(_player.getLives()) + "\n"
			+ "You ate " + std::to_string(_player.getScore() / 10) + " apples");
		_deltaTime -= sf::seconds(fps);
		
		if (_player.isAlive())
		{
			_player.newGame();
		}
	}
}

void Game::Render()
{ 
	_window.BeginDraw();

	_world.render(*_window.getWindow());
	_player.render(*_window.getWindow());
	_window.Draw(_scoreTable);

	_window.EndDraw();
}


sf::Time Game::GetDeltaTime()
{
	return _deltaTime;
}

void Game::RestartClock()
{
	_deltaTime += _clock.restart();
}