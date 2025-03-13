#pragma once
#include <SFML/Graphics.hpp>
#include "Basket.h"

constexpr float DEFAULT_GRAVITY = 75.0f;
constexpr float LAUNCH_CONSTANT = 3;

class Ball : public sf::Drawable {
public:
	Ball(float radius);

	void update(float dt, sf::RenderWindow& window, Basket& basket);
	void setCenterPosition(sf::Vector2f position);
	void initializeVelocity(sf::Vector2f velocity);
	bool checkIfClicked(sf::Vector2f position);
	void launch(sf::Vector2f start, sf::Vector2f end);

private:
	sf::CircleShape m_circle;
	sf::Vector2f m_velocity;
	float m_gravity;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void collisionHandler(sf::RenderWindow& window, Basket& basket);
	void updateVelocityWithGravity(float dt);
	void setGravity(float gravity);
};