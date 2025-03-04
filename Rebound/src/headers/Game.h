#pragma once

#include <SFML/Graphics.hpp>

constexpr int HEIGHT = 800;
constexpr int WIDTH = 500;
enum GameState { MainMenu, InGame };

class Game {
public:
	/*enum GameState { MainMenu, InGame };*/

public:
	Game();

	void run();
	GameState getGameState();
	void setGameState(GameState gameState);


private:
	sf::RenderWindow m_window;
	sf::CircleShape m_target_circle;
	sf::RectangleShape m_player_rect;
	GameState m_game_state;

private:
	void handleEvents();
	void handleKeyPress(sf::Keyboard::Scancode code);
	void handleInGameEvents(const sf::Event& event);
	void handleMainMenuEvents(const sf::Event& event);
};

