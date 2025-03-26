#pragma once

#include <SFML/Graphics.hpp>
#include "CollisionResult.h"

constexpr int BASKET_WIDTH = 30;
constexpr int BASKET_HEIGHT = 30;
constexpr int BASKET_THICKNESS = 5;

class Basket : public sf::Drawable {
public:
	Basket();

	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition();
	CollisionResult getHitDirection(sf::Vector2f position, float radius);
	bool hitCenter(sf::CircleShape circle) const;

private:
	std::array<sf::RectangleShape, 3> m_basket_rects;
	sf::Vector2f m_center_position;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};