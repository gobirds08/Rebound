#include "Game.h"

Game::Game() {
	m_window.create(sf::VideoMode({ HEIGHT, WIDTH }), "Rebound", sf::Style::Titlebar | sf::Style::Close);
	//m_target_circle = sf::CircleShape(50);
    m_game_state = GameState::MainMenu;
}

GameState Game::getGameState() {
    return m_game_state;
}

void Game::setGameState(GameState gameState) {
    m_game_state = gameState;
}

void Game::run() {
    while (m_window.isOpen()) {
        handleEvents();

        m_window.clear();

        // TODO: Draw Shapes In Game 

        m_window.display();
    }
}

void Game::handleEvents() {
    while (const std::optional event = m_window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            m_window.close();
        } 

        if (m_game_state == GameState::InGame) {
            handleInGameEvents(event.value());
        }
        else if (m_game_state == GameState::MainMenu) {
            handleMainMenuEvents(event.value());
        }
    }
}


void Game::handleInGameEvents(const sf::Event& event) {
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        handleKeyPress(keyPressed->scancode);
    } 

    // TODO: Handle Mouse Movement For Player
}

void Game::handleMainMenuEvents(const sf::Event& event) {
    // TODO: Implementation
}

void Game::handleKeyPress(sf::Keyboard::Scancode code) {
    switch (code) {
        case sf::Keyboard::Scancode::Escape:
            m_window.close();
            break;
        case sf::Keyboard::Scancode::Up:
            break;
        case sf::Keyboard::Scancode::Down:
            break;
        case sf::Keyboard::Scancode::Right:
            break;
        case sf::Keyboard::Scancode::Left:
            break;
        default:
            break;
    }
}