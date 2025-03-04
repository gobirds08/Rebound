#pragma once

#include <SFML/Graphics.hpp>

constexpr int HEIGHT = 500;
constexpr int WIDTH = 800;
constexpr int MAIN_MENU_ARR_SIZE = 3;
enum GameState { MainMenu, InGame };

class Game {
public:
	/*enum GameState { MainMenu, InGame };*/

public:
	Game();

	void run();
	GameState getGameState() const;
	void setGameState(GameState gameState);


private:
	sf::RenderWindow m_window;
	sf::CircleShape m_target_circle;
	sf::RectangleShape m_player_rect;
	GameState m_game_state;
	sf::RectangleShape m_main_menu_rects[MAIN_MENU_ARR_SIZE];

private:
	void handleEvents();
	void handleKeyPress(sf::Keyboard::Scancode code);
	void handleInGameEvents(const sf::Event& event);
	void handleMainMenuEvents(const sf::Event& event);
	void initMainMenu();
};

