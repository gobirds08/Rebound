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

void Basket::spawnRandomPosition(sf::RenderWindow& window) {
    sf::Vector2u window_size = window.getSize();
    sf::Vector2u max = { window_size.x - BASKET_WIDTH * 3, window_size.y - BASKET_HEIGHT * 3};
    sf::Vector2u min = { BASKET_WIDTH * 3, BASKET_HEIGHT * 3 };

    int x = RandomUtils::getRandomInt(min.x, max.x);
    int y = RandomUtils::getRandomInt(min.y, max.y);

    setPosition({ static_cast<float>(x), static_cast<float>(y) });
}

sf::Vector2f Basket::getPosition() {
	return m_center_position;
}

CollisionResult Basket::getHitDirection(sf::Vector2f position, float radius) {
    for (int i = 0; i < 3; i++) {
        sf::Vector2f rectCenter = m_basket_rects[i].getPosition();
        sf::Vector2f rectSize = m_basket_rects[i].getSize();

        sf::Vector2f rectTopLeft = rectCenter - (rectSize / 2.0f);

        sf::Vector2f expandedPosition = rectTopLeft - sf::Vector2f(radius, radius);
        sf::Vector2f expandedSize = rectSize + sf::Vector2f(2 * radius, 2 * radius);

        if (position.x >= expandedPosition.x && position.x <= expandedPosition.x + expandedSize.x &&
            position.y >= expandedPosition.y && position.y <= expandedPosition.y + expandedSize.y) {

            float overlapLeft = (position.x + radius) - rectTopLeft.x;
            float overlapRight = (rectTopLeft.x + rectSize.x) - (position.x - radius);
            float overlapTop = (position.y + radius) - rectTopLeft.y;
            float overlapBottom = (rectTopLeft.y + rectSize.y) - (position.y - radius);

            float minOverlapX = std::min(overlapLeft, overlapRight);
            float minOverlapY = std::min(overlapTop, overlapBottom);

            CollisionResult result;
            result.newPosition = position;

            if (minOverlapX < minOverlapY) {
                result.hitDirection = { -1, 1 };  // Left or Right hit

                if (overlapLeft < overlapRight)
                    result.newPosition.x = rectTopLeft.x - radius - 0.1f;
                else
                    result.newPosition.x = rectTopLeft.x + rectSize.x + radius + 0.1f; 
            }
            else {
                result.hitDirection = { 1, -1 }; // Top or Bottom Hit

                if (overlapTop < overlapBottom)
                    result.newPosition.y = rectTopLeft.y - radius - 0.1f;
                else
                    result.newPosition.y = rectTopLeft.y + rectSize.y + radius + 0.1f;
            }

            return result;
        }
    }

    return { position, {1, 1} };
}

bool Basket::hitCenter(sf::CircleShape circle) const {
    sf::FloatRect rectBounds = circle.getGlobalBounds();
    if (rectBounds.contains(m_center_position)) {
        return true;
    }
    return false;
}





void Basket::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_basket_rects[0], states);
	target.draw(m_basket_rects[1], states);
	target.draw(m_basket_rects[2], states);
}