#include "Game.h"

Game::Game() {
	m_window.create(sf::VideoMode({ WIDTH, HEIGHT }), "Rebound", sf::Style::Titlebar | sf::Style::Close);
	//m_target_circle = sf::CircleShape(50);
    m_game_state = GameState::MainMenu;
    if (!m_font.openFromFile("fonts/arial.ttf")) {
        throw std::runtime_error("Failed to load font");
    }
    initMainMenu();
}

void Game::initMainMenu() {
    m_main_menu_buttons.emplace_back("Start", sf::Vector2f{ 300, 50 }, m_font);
    m_main_menu_buttons.emplace_back("Help", sf::Vector2f{ 300, 50 }, m_font);
    m_main_menu_buttons.emplace_back("Quit", sf::Vector2f{ 300, 50 }, m_font);
    

    // TODO: Set Other Button Actions Here
    m_main_menu_buttons[2].setOnClick([this]() {
        m_window.close();
    });

    const float HEIGHT_COL = HEIGHT / 4;
    const float WIDTH_CENTER = WIDTH / 2;

    for (int i = 0; i < m_main_menu_buttons.size(); i++) {
        m_main_menu_buttons[i].setCenterPosition(WIDTH_CENTER, HEIGHT_COL * i + HEIGHT_COL);
    }
    
}

GameState Game::getGameState() const {
    return m_game_state;
}

void Game::setGameState(GameState gameState) {
    m_game_state = gameState;
}

void Game::run() {
    while (m_window.isOpen()) {
        handleEvents();

        m_window.clear();

        for (int i = 0; i < m_main_menu_buttons.size(); i++) {
            m_window.draw(m_main_menu_buttons[i]);
        }

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
    if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
            handleMouseLeftClick((sf::Vector2f)mouseButtonPressed->position);
        }
    }
}

void Game::handleMouseLeftClick(sf::Vector2f position) {
    // Loop through buttons in "scene" and see if we clicked it
    // If so, then call, the button's onClick method
    for (int i = 0; i < m_main_menu_buttons.size(); i++) {
        if (m_main_menu_buttons[i].checkIfClicked(position)) {
            m_main_menu_buttons[i].onClick();
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