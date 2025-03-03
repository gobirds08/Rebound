#include "Game.h"

Game::Game() {
	m_window.create(sf::VideoMode({ HEIGHT, WIDTH }), "Rebound", sf::Style::Titlebar | sf::Style::Close);
}

void Game::run() {
    while (m_window.isOpen()) {
        handleEvents();

        m_window.clear();
        m_window.display();
    }
}

void Game::handleEvents() {
    while (const std::optional event = m_window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            m_window.close();
        } 
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            handleKeyPress(keyPressed->scancode);
        }
    }
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