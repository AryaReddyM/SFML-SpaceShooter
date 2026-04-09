#pragma once

#include <SFML/Graphics.hpp>

class Player {
public:
	Player(sf::Vector2f startPos, sf::RenderWindow& window);
	void Draw();
	void Move();
	void ChangeXDir(float dirX);
	void ChangeYDir(float dirY);
	bool OutOfBounds();

	sf::Sprite ship;
	sf::Texture icon;
	sf::Vector2f pos;
	sf::Vector2f vel;
	sf::FloatRect bounds;
	float speed = 0.75f;

	sf::RenderWindow& window;
};