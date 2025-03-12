#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Ball.h"
#include "Basket.h"
#include <vector>

constexpr int HEIGHT = 500;
constexpr int WIDTH = 800;
enum GameState { MainMenu, InGame };

class Game {
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
	sf::Font m_font;
	std::vector<std::shared_ptr<sf::Drawable>> m_shapes;
	std::shared_ptr<Ball> m_ball;
	std::unique_ptr<Basket> m_basket;
	bool m_isDragging;
	sf::Vector2f m_start_drag;
	sf::Vector2f m_end_drag;
	

private:
	void handleEvents();
	void handleKeyPress(sf::Keyboard::Scancode code);
	void handleInGameEvents(const sf::Event& event);
	void handleMainMenuEvents(const sf::Event& event);
	void handleMouseLeftClick(sf::Vector2f position);
	void initMainMenu();
	void initInGame();
};

