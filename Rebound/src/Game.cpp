#include "Game.h"

Game::Game() {
	m_window.create(sf::VideoMode({ WIDTH, HEIGHT }), "Rebound", sf::Style::Titlebar | sf::Style::Close);
	//m_target_circle = sf::CircleShape(50);
    m_game_state = GameState::MainMenu;
    initMainMenu();
}

void Game::initMainMenu() {
    sf::RectangleShape button_start({ 300, 50 });
    sf::RectangleShape button_help({ 300, 50 });
    sf::RectangleShape button_quit({ 300, 50 });

    m_main_menu_rects[0] = button_start;
    m_main_menu_rects[1] = button_help;
    m_main_menu_rects[2] = button_quit;

    const float HEIGHT_COL = HEIGHT / 4;
    const float WIDTH_CENTER = WIDTH / 2;

    for (int i = 0; i < MAIN_MENU_ARR_SIZE; i++) {
        m_main_menu_rects[i].setOrigin({ 150.0f, 25.0f });
        m_main_menu_rects[i].setPosition({ WIDTH_CENTER, HEIGHT_COL * i + HEIGHT_COL });
        m_main_menu_rects[i].setFillColor(sf::Color::White);
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

        // TODO: Draw Shapes In Game
        for (int i = 0; i < MAIN_MENU_ARR_SIZE; i++) {
            m_window.draw(m_main_menu_rects[i]);
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