#pragma once

#include "SFML/Graphics.hpp"

class Enemy {
public:
	Enemy(sf::Vector2f pos, sf::RenderWindow& window, const sf::Texture& texture);
	void Draw();
	void Move();
	bool OutOfBounds();
	bool Shot(sf::FloatRect otherBounds);

	sf::Sprite ship;
	sf::Vector2f pos;
	sf::Vector2f vel;
	sf::FloatRect bounds;
	float speed = 0.5f;
	int dir = 1;

	bool shouldDie = false;

	sf::RenderWindow* window;
};