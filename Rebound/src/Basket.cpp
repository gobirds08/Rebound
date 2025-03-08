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
}


void Basket::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_basket_rects[0], states);
	target.draw(m_basket_rects[1], states);
	target.draw(m_basket_rects[2], states);
}