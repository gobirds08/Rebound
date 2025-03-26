#pragma once
#include <SFML/Graphics.hpp>
#include "Basket.h"
#include "CollisionResult.h"

constexpr float DEFAULT_GRAVITY = 90.0f;
constexpr float LAUNCH_CONSTANT = 2;

class Ball : public sf::Drawable {
public:
	Ball(float radius);

	void update(float dt, sf::RenderWindow& window, std::shared_ptr<Basket> basket);
	void setCenterPosition(sf::Vector2f position);
	void initializeVelocity(sf::Vector2f velocity);
	bool checkIfClicked(sf::Vector2f position);
	void launch(sf::Vector2f start, sf::Vector2f end);
	bool isMoving();

private:
	sf::CircleShape m_circle;
	sf::Vector2f m_velocity;
	float m_gravity;
	bool m_is_colliding;
	bool m_is_moving;
	int m_hit_count;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void collisionHandler(sf::RenderWindow& window, std::shared_ptr<Basket> basket);
	void updateVelocityWithGravity(float dt);
	void setGravity(float gravity);
};