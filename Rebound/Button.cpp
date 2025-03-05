#include "Button.h"

Button::Button(const std::string& text, const sf::Vector2f& size, const sf::Font& font, unsigned int charSize) 
    : m_text(font)
{
    m_text.setString(text);
    m_text.setCharacterSize(charSize);
    m_text.setFillColor(sf::Color::Red);

    m_rectangle.setSize(size);
    m_rectangle.setOrigin({ size.x / 2, size.y / 2 });

    setCenterPosition(size.x / 2, size.y / 2);
}

void Button::setCenterPosition(float x, float y) {
    m_rectangle.setPosition({ x, y });
    centerText();
}

void Button::centerText() {
    sf::FloatRect textBounds = m_text.getLocalBounds();
    sf::Vector2f rect_center = m_rectangle.getGlobalBounds().getCenter();

    m_text.setOrigin({ textBounds.size.x / 2, textBounds.size.y / 2 + textBounds.position.y});
    m_text.setPosition(rect_center);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_rectangle, states);
    target.draw(m_text, states);
}