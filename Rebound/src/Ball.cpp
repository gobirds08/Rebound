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

void Ball::update(float dt, sf::RenderWindow& window, std::shared_ptr<Basket> basket) {
	// Maybe Collision Handler Can Take In A Vector Of Shapes That Should Collide
	collisionHandler(window, basket);
	updateVelocityWithGravity(dt);
	sf::Vector2f circle_position = m_circle.getPosition();
	float x = circle_position.x + m_velocity.x * dt;
	float y = circle_position.y + m_velocity.y * dt;
	setCenterPosition({ x, y });
}

void Ball::updateVelocityWithGravity(float dt) {
	m_velocity.y += m_gravity * dt;
}

bool Ball::checkIfClicked(sf::Vector2f position) {
	sf::FloatRect rectBounds = m_circle.getGlobalBounds();
	if (rectBounds.contains(position)) {
		return true;
	}
	return false;
}

void Ball::launch(sf::Vector2f start, sf::Vector2f end) {
	sf::Vector2f launch_velocity;
	launch_velocity.x = LAUNCH_CONSTANT * (start.x - end.x);
	launch_velocity.y = LAUNCH_CONSTANT * (start.y - end.y);
	m_velocity = launch_velocity;
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_circle, states);

	// Test Text

	sf::Font font;
	if (!font.openFromFile("fonts/arial.ttf")) {
		throw std::runtime_error("Failed to load font");
	}
	sf::Text y_text(font, std::to_string(m_velocity.y));
	y_text.setPosition({ 600, 50 });
	target.draw(y_text, states);
}

void Ball::collisionHandler(sf::RenderWindow& window, std::shared_ptr<Basket> basket) {
	
	sf::Vector2f position = m_circle.getPosition();
	float radius = m_circle.getRadius();
	{
		sf::Vector2u window_size = window.getSize();

		// TODO: Handle collisions on bottom when ball is towards end of bouncing

		if (position.y - radius <= 1) {
			m_velocity.y *= -.8;
			m_velocity.x *= .999;
			m_circle.setPosition({ position.x, radius + 1 });
		}
		if (position.y + radius >= window_size.y) {
			m_velocity.y *= -.8;
			m_velocity.x *= .999;
			m_circle.setPosition({ position.x, window_size.y - radius - 1 });
		}
		if (position.x - radius <= 0) {
			m_velocity.x *= -.8;
			m_circle.setPosition({ radius + 1, position.y });
		}
		if (position.x + radius >= window_size.x) {
			m_velocity.x *= -.8;
			m_circle.setPosition({ window_size.x - radius - 1, position.y });
		}
	}
	// May Need To Implement More For Other Potential Objects

	// Handle Basket Collision Here
	sf::Vector2f hitDirection = basket->getHitDirection(position);
	m_velocity.x *= hitDirection.x;
	m_velocity.y *= hitDirection.y;
}