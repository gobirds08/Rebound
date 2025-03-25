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

CollisionResult Basket::getHitDirection(sf::Vector2f position, float radius) {
    for (int i = 0; i < 3; i++) {
        // Retrieve the rectangle's position (center) and size
        sf::Vector2f rectCenter = m_basket_rects[i].getPosition();
        sf::Vector2f rectSize = m_basket_rects[i].getSize();

        // Calculate the true top-left corner of the rectangle
        sf::Vector2f rectTopLeft = rectCenter - (rectSize / 2.0f);

        // Calculate the expanded area of the rectangle by the ball's radius
        sf::Vector2f expandedPosition = rectTopLeft - sf::Vector2f(radius, radius);
        sf::Vector2f expandedSize = rectSize + sf::Vector2f(2 * radius, 2 * radius);

        // Check if the ball is within the expanded bounds
        if (position.x >= expandedPosition.x && position.x <= expandedPosition.x + expandedSize.x &&
            position.y >= expandedPosition.y && position.y <= expandedPosition.y + expandedSize.y) {

            // Calculate overlap distances in X and Y directions
            float overlapLeft = (position.x + radius) - rectTopLeft.x;
            float overlapRight = (rectTopLeft.x + rectSize.x) - (position.x - radius);
            float overlapTop = (position.y + radius) - rectTopLeft.y;
            float overlapBottom = (rectTopLeft.y + rectSize.y) - (position.y - radius);

            // Find the smallest overlap to determine collision direction
            float minOverlapX = std::min(overlapLeft, overlapRight);
            float minOverlapY = std::min(overlapTop, overlapBottom);

            CollisionResult result;
            result.newPosition = position;

            if (minOverlapX < minOverlapY) {
                result.hitDirection = { -1, 1 };  // Left or Right hit

                // Adjust position based on where the collision occurred
                if (overlapLeft < overlapRight)
                    result.newPosition.x = rectTopLeft.x - radius - 0.1f; // Push left
                else
                    result.newPosition.x = rectTopLeft.x + rectSize.x + radius + 0.1f; // Push right
            }
            else {
                result.hitDirection = { 1, -1 };  // Top or Bottom hit

                // Adjust position based on where the collision occurred
                if (overlapTop < overlapBottom)
                    result.newPosition.y = rectTopLeft.y - radius - 0.1f; // Push above
                else
                    result.newPosition.y = rectTopLeft.y + rectSize.y + radius + 0.1f; // Push below
            }

            return result;  // Return the new position and the hit direction
        }
    }

    // No collision detected, return original position and neutral hit direction
    return { position, {1, 1} };
}





void Basket::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_basket_rects[0], states);
	target.draw(m_basket_rects[1], states);
	target.draw(m_basket_rects[2], states);
}