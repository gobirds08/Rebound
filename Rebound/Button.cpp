#include "Button.h"

Button::Button(const std::string& text, const sf::Vector2f& size, const sf::Font& font, unsigned int charSize) 
    : m_text(font)
{
    m_text.setString(text);
    m_text.setCharacterSize(charSize);
    m_text.setFillColor(sf::Color::Red);

    m_rectangle.setSize(size);

    setPosition(0, 0);
}

void Button::setPosition(float x, float y) {
    m_rectangle.setPosition({ x, y });
    centerText();
}

void Button::centerText() {
    sf::FloatRect textBounds = m_text.getLocalBounds();
    sf::FloatRect rectBounds = m_rectangle.getGlobalBounds();

    // TODO: CENTER HERE
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_rectangle, states);
    target.draw(m_text, states);
}