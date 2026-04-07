#pragma once

#include <SFML/Graphics.hpp>
#include "Player/Player.h"
#include "Bullet/BulletHandler.h"

class Game {
public:
	Game();
	void HandleInput();

	sf::RenderWindow window = sf::RenderWindow();
	sf::Vector2u res = sf::VideoMode::getDesktopMode().size;

	Player* player;
	BulletHandler* bullet;

	float shotCooldown = 0.5f;
	float lastTime = 0.0f;
	sf::Clock clock;
};