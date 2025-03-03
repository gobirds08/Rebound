#include "Game.h"

Game::Game() {
	m_window.create(sf::VideoMode({ HEIGHT, WIDTH }), "Rebound", sf::Style::Titlebar | sf::Style::Close);
}

void Game::Run() {
    while (m_window.isOpen())
    {
        while (const std::optional event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                m_window.close();
        }

        m_window.clear();
        m_window.display();
    }
}