#pragma once
#include <SFML/Graphics.hpp>

constexpr float DEFAULT_GRAVITY = 75.0f;

class Ball : public sf::Drawable {
public:
	Ball(float radius);

	void update(float dt, sf::RenderWindow& window);
	void setCenterPosition(sf::Vector2f position);
	void initializeVelocity(sf::Vector2f velocity);

private:
	sf::CircleShape m_circle;
	sf::Vector2f m_velocity;
	float m_gravity;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void collisionHandler(sf::RenderWindow& window);
	void updateVelocityWithGravity(float dt);
	void setGravity(float gravity);
};