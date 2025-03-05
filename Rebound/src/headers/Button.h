#pragma once

#include <SFML/Graphics.hpp>

class Button : public sf::Drawable {
public:
	Button(const std::string& text, const sf::Vector2f& size, const sf::Font& font, unsigned int charSize = 24);

	void setPosition(float x, float y);

private:
	sf::RectangleShape m_rectangle;
	sf::Text m_text;

private:
	void centerText();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};