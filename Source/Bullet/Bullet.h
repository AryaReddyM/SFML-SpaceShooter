#pragma once

#include <SFML/Graphics.hpp>

class Bullet {
public:
	Bullet(sf::Vector2f pos);
	void Draw(sf::RenderWindow& window);
	void Move();

	sf::RectangleShape proj;
	sf::FloatRect bounds;
	sf::Vector2f pos;
	float speed = 1.0;
};