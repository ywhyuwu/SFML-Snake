#include "window.h"

window::window()
{
	Setup("Game", sf::Vector2u(800, 600));
}

window::window(const std::string& name)
{
	Setup(name, sf::Vector2u(800, 600));
}

window::window(const std::string& name, const sf::Vector2u& size)
{
	Setup(name, size);
}

window::~window()
{
	DestroyWindow();
}

void window::Setup(const std::string& name, const sf::Vector2u& size)
{
	_winName = name;
	_winSize = size;
	_isClosed = false;
	_isFullscreen = false;
	CreateWindow();
}

void window::CreateWindow()
{
	auto style = (_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	_window.create(sf::VideoMode(_winSize.x, _winSize.y), _winName, style);
}

void window::DestroyWindow()
{
	_window.close();
}

void window::Update()
{
	sf::Event ev;

	while (_window.pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed)
			_isClosed = true;
		else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::F10)
			SwitchFullscreen();
	}
}

void window::SwitchFullscreen()
{
	_isFullscreen = !_isFullscreen;
	DestroyWindow();
	CreateWindow();
}

void window::BeginDraw()
{
	_window.clear(sf::Color(255, 150, 208, 1));
}

void window::EndDraw()
{
	_window.display();
}

void window::Draw(sf::Drawable& object)
{
	_window.draw(object);
}

bool window::isClosed()
{
	return _isClosed;
}

bool window::isFullscreen()
{
	return _isFullscreen;
}

sf::Vector2u window::GetWindowSize()
{
	return _winSize;
}

sf::RenderWindow* window::getWindow()
{
	return &_window;
}