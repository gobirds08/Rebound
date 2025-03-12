#include "Ball.h"
#include <iostream>

Ball::Ball(float radius) :
	m_circle(radius)
{
	m_circle.setOrigin({ radius, radius });
	m_velocity = { 0, 0 };
	m_gravity = DEFAULT_GRAVITY;
}

void Ball::setCenterPosition(sf::Vector2f position) {
	m_circle.setPosition(position);
}

void Ball::setGravity(float gravity) {
	m_gravity = gravity;
}

void Ball::initializeVelocity(sf::Vector2f velocity) {
	m_velocity = velocity;
}

void Ball::update(float dt, sf::RenderWindow& window) {
	// Maybe Collision Handler Can Take In A Vector Of Shapes That Should Collide
	collisionHandler(window);
	updateVelocityWithGravity(dt);
	sf::Vector2f circle_position = m_circle.getPosition();
	float x = circle_position.x + m_velocity.x * dt;
	float y = circle_position.y + m_velocity.y * dt;
	if (y + m_circle.getRadius() > window.getSize().y) {
		y = (int)(window.getSize().y - m_circle.getRadius());
	}
	setCenterPosition({ x, y });
}

void Ball::updateVelocityWithGravity(float dt) {
	//if (m_velocity.y < 0.05) {
	//	m_velocity.y = 0;
	//}
	//if (m_velocity.x < 0.05) {
	//	m_velocity.x = 0;
	//}
	m_velocity.y += m_gravity * dt;
	
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_circle, states);

	// Test Text

	sf::Font font;
	if (!font.openFromFile("fonts/arial.ttf")) {
		throw std::runtime_error("Failed to load font");
	}
	sf::Text y_text(font, std::to_string(m_velocity.x));
	y_text.setPosition({ 600, 50 });
	target.draw(y_text, states);
}

void Ball::collisionHandler(sf::RenderWindow& window) {
	sf::Vector2f position = m_circle.getPosition();
	float radius = m_circle.getRadius();
	sf::Vector2u window_size = window.getSize();
	std::cout << m_velocity.x << std::endl;
	if (position.y - radius <= 0) {
		m_velocity.y *= -.8;
		m_velocity.x *= .999;
	}
	if (position.y + radius >= window_size.y) {
		m_velocity.y *= -.8;
		m_velocity.x *= .999;
	}
	if (position.x - radius <= 0) {
		m_velocity.x *= -.8;
		m_circle.setPosition({ radius + 1, position.y });
	}
	if (position.x + radius >= window_size.x) {
		m_velocity.x *= -.8;
		m_circle.setPosition({ window_size.x - radius - 1, position.y });
	}

	// May Need To Implement More For Other Potential Objects
}