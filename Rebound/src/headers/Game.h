#pragma once

#include <SFML/Graphics.hpp>

constexpr int HEIGHT = 800;
constexpr int WIDTH = 500;

class Game {
public:
	Game();

	void run();

private:
	sf::RenderWindow m_window;

private:
	void handleEvents();
	void handleKeyPress(sf::Keyboard::Scancode code);
};

