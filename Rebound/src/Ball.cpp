#include "Ball.h"

Ball::Ball(float radius) :
	m_circle(radius)
{
	m_circle.setOrigin({ radius, radius });
}

void Ball::setCenterPosition(sf::Vector2f position) {
	m_circle.setPosition(position);
}

void Ball::update(float dt) {

}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_circle, states);
}