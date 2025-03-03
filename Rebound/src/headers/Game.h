#pragma once

#include <SFML/Graphics.hpp>

constexpr int HEIGHT = 800;
constexpr int WIDTH = 500;

class Game {
public:
	Game();

	void Run();

private:
	sf::RenderWindow m_window;
};

