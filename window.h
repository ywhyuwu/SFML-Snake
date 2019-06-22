#pragma once

#include <SFML/Graphics.hpp>

class window
{
public:
	window();
	window(const std::string& name);
	window(const std::string& name, const sf::Vector2u& size);
	~window();

	void BeginDraw();
	void EndDraw();
	
	void Update();

	bool isClosed();
	bool isFullscreen();
	sf::Vector2u GetWindowSize();

	sf::RenderWindow* getWindow();

	void SwitchFullscreen();

	void Draw(sf::Drawable& object);
private:
	void Setup(const std::string& name, const sf::Vector2u& size);
	void DestroyWindow();
	void CreateWindow();

	sf::RenderWindow _window;
	sf::Vector2u _winSize;
	std::string _winName;
	bool _isClosed;
	bool _isFullscreen;
};