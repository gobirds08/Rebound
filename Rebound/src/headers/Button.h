#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

class Button : public sf::Drawable {
public:
	Button(const std::string& text, const sf::Vector2f& size, const sf::Font& font, unsigned int charSize = 24);

	void setCenterPosition(float x, float y);
	void onClick();
	bool checkIfClicked(sf::Vector2f position);
	void setOnClick(std::function<void()> func);

private:
	sf::RectangleShape m_rectangle;
	sf::Text m_text; 
	std::function<void()> m_onClick;

private:
	void centerText();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};