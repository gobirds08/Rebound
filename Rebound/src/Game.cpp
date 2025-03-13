#include "Game.h"
#include <iostream>

Game::Game()
{
	m_window.create(sf::VideoMode({ WIDTH, HEIGHT }), "Rebound", sf::Style::Titlebar | sf::Style::Close);
    m_game_state = GameState::MainMenu;
    if (!m_font.openFromFile("fonts/arial.ttf")) {
        throw std::runtime_error("Failed to load font");
    }
    initMainMenu();
    m_isDragging = false;
}

void Game::initMainMenu() {
    m_shapes.clear();
    const float HEIGHT_COL = HEIGHT / 4;
    const float WIDTH_CENTER = WIDTH / 2;

    std::shared_ptr<Button> ptr_button_start = std::make_shared<Button>("Start", sf::Vector2f{ 300, 50 }, m_font);
    std::shared_ptr<Button> ptr_button_help = std::make_shared<Button>("Help", sf::Vector2f{ 300, 50 }, m_font);
    std::shared_ptr<Button> ptr_button_quit = std::make_shared<Button>("Quit", sf::Vector2f{ 300, 50 }, m_font);

    ptr_button_start->setOnClick([this]() {
        initInGame();
    });

    ptr_button_quit->setOnClick([this]() {
        m_window.close();
    });

    m_shapes.push_back(ptr_button_start);
    m_shapes.push_back(ptr_button_help);
    m_shapes.push_back(ptr_button_quit);

    for (int i = 0; i < m_shapes.size(); i++) {
        static_cast<Button*>(m_shapes[i].get())->setCenterPosition(WIDTH_CENTER, HEIGHT_COL * i + HEIGHT_COL);
    }
}

void Game::initInGame() {
    m_shapes.clear();
    m_ball = std::make_shared<Ball>(10.0f);
    m_ball->setCenterPosition({ 100.0f, 400.0f });
    /*m_ball->initializeVelocity({200, -50});*/
    m_shapes.push_back(m_ball);

    m_basket = std::make_unique<Basket>();
    m_basket->setPosition({ 200, 100 });
    m_shapes.push_back(std::move(m_basket));

    m_game_state = GameState::InGame;
}

GameState Game::getGameState() const {
    return m_game_state;
}

void Game::setGameState(GameState gameState) {
    m_game_state = gameState;
}

void Game::run() {
    sf::Clock clock;

    while (m_window.isOpen()) {
        sf::Time elapsedTime = clock.restart();
        float deltaTime = elapsedTime.asSeconds();

        handleEvents();

        m_window.clear();

        if (m_game_state == GameState::InGame) {
            m_ball->update(deltaTime, m_window, *m_basket);
        }

        // TODO: Call Update Function and pass in dt and maybe gameState
        for (const auto& shape : m_shapes) {
            m_window.draw(*shape);
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
    /*if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        handleKeyPress(keyPressed->scancode);
    }*/
    if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
            if (m_ball->checkIfClicked((sf::Vector2f)mouseButtonPressed->position)) {
                m_isDragging = true;
                m_start_drag = (sf::Vector2f)mouseButtonPressed->position;
            }
        }
    }
    if (const auto* mouseButtonReleased = event.getIf<sf::Event::MouseButtonReleased>()) {
        if (mouseButtonReleased->button == sf::Mouse::Button::Left) {
            if (m_isDragging) {
                m_isDragging = false;
                m_end_drag = (sf::Vector2f)mouseButtonReleased->position;
                m_ball->launch(m_start_drag, m_end_drag);
            }
        }
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

    for (int i = 0; i < m_shapes.size(); i++) {
        if (auto* shape = dynamic_cast<Button*>(m_shapes[i].get())) {
            if (shape->checkIfClicked(position)) {
                shape->onClick();
            }
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