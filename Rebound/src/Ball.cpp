#include "Ball.h"

Ball::Ball(float radius) :
	m_circle(radius)
{
	m_circle.setOrigin({ radius, radius });
	m_velocity = { 0, 0 };
}

void Ball::setCenterPosition(sf::Vector2f position) {
	m_circle.setPosition(position);
}

void Ball::initializeVelocity(sf::Vector2f velocity) {
	m_velocity = velocity;
}

void Ball::update(float dt, sf::RenderWindow& window) {
	// Maybe Collision Handler Can Take In A Vector Of Shapes That Should Collide
	collisionHandler(window);
	sf::Vector2f circle_position = m_circle.getPosition();
	float x = circle_position.x + m_velocity.x * dt;
	float y = circle_position.y + m_velocity.y * dt;
	setCenterPosition({ x, y });
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_circle, states);
}

void Ball::collisionHandler(sf::RenderWindow& window) {
	sf::Vector2f position = m_circle.getPosition();
	float radius = m_circle.getRadius();
	sf::Vector2u window_size = window.getSize();
	
	if (position.y - radius <= 0) {
		m_velocity.y *= -1;
	}
	if (position.y + radius >= window_size.y) {
		m_velocity.y *= -1;
	}
	if (position.x - radius <= 0) {
		m_velocity.x *= -1;
	}
	if (position.x + radius >= window_size.x) {
		m_velocity.x *= -1;
	}

	// May Need To Implement More For Other Potential Objects
}