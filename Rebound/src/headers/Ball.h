#pragma once
#include <SFML/Graphics.hpp>

class Ball : public sf::Drawable {
public:
	Ball(float radius);

	void update(float dt);
	void setCenterPosition(sf::Vector2f position);

private:
	sf::CircleShape m_circle;
	sf::Vector2f m_velocity;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};