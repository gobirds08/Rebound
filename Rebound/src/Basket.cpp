#include <Basket.h>

Basket::Basket() {
	m_basket_rects[0] = sf::RectangleShape({ BASKET_THICKNESS, BASKET_HEIGHT });
	m_basket_rects[1] = sf::RectangleShape({ BASKET_WIDTH, BASKET_THICKNESS });
	m_basket_rects[2] = sf::RectangleShape({ BASKET_THICKNESS, BASKET_HEIGHT });

	m_basket_rects[0].setOrigin({ BASKET_THICKNESS / 2, BASKET_HEIGHT / 2 });
	m_basket_rects[1].setOrigin({ BASKET_WIDTH / 2, BASKET_THICKNESS / 2 });
	m_basket_rects[2].setOrigin({ BASKET_THICKNESS / 2, BASKET_HEIGHT / 2 });
}

void Basket::setPosition(sf::Vector2f position) {
	m_basket_rects[0].setPosition({ position.x - (BASKET_WIDTH / 2) - (BASKET_THICKNESS / 2), position.y});
	m_basket_rects[1].setPosition({ position.x, position.y + (BASKET_HEIGHT / 2) - (BASKET_THICKNESS / 2)});
	m_basket_rects[2].setPosition({ position.x + (BASKET_WIDTH / 2) + (BASKET_THICKNESS / 2), position.y });
	
	m_center_position = position;
}

sf::Vector2f Basket::getPosition() {
	return m_center_position;
}

sf::Vector2f Basket::getHitDirection(sf::Vector2f position, float radius) {
	for (int i = 0; i < 3; i++) {
		sf::FloatRect rectBounds = m_basket_rects[i].getGlobalBounds();

		sf::Vector2f expandedPosition = rectBounds.position - sf::Vector2f(radius, radius);
		sf::Vector2f expandedSize = rectBounds.size + sf::Vector2f(2 * radius, 2 * radius);

		if (position.x >= expandedPosition.x && position.x <= expandedPosition.x + expandedSize.x &&
			position.y >= expandedPosition.y && position.y <= expandedPosition.y + expandedSize.y) {

			// Calculate distances from the original (non-expanded) rectangle
			float leftDist = std::abs(position.x - rectBounds.position.x);
			float rightDist = std::abs(position.x - (rectBounds.position.x + rectBounds.size.x));
			float topDist = std::abs(position.y - rectBounds.position.y);
			float bottomDist = std::abs(position.y - (rectBounds.position.y + rectBounds.size.y));

			float minDist = std::min({ leftDist, rightDist, topDist, bottomDist });

			if (minDist == leftDist || minDist == rightDist) {
				return { -1, 1 }; 
			}
			else {
				return { 1, -1 }; 
			}
		}
	}

	return { 1, 1 };
}

void Basket::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_basket_rects[0], states);
	target.draw(m_basket_rects[1], states);
	target.draw(m_basket_rects[2], states);
}