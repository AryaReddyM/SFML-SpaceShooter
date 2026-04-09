#pragma once

#include <SFML/Graphics.hpp>
#include "Player/Player.h"
#include "Bullet/BulletHandler.h"
#include "Enemy/EnemyHandler.h"

class Game {
public:
	Game();
	void HandleInput();
	void HandleCollisions();
	void HandleGameOver();
	void Reset();

	sf::RenderWindow window = sf::RenderWindow();
	sf::Vector2u res = sf::VideoMode::getDesktopMode().size;

	Player* player;
	BulletHandler* bullet;
	EnemyHandler* enemy;

	float shotCooldown = 0.5f;
	float lastTime = 0.0f;
	sf::Clock clock;

	bool gameOver = false;
	float gameOverTime = 0.0f;
	float restartDelay = 2.0f;

	sf::Font font;
	std::unique_ptr<sf::Text> waveText;
	std::unique_ptr<sf::Text> gameOverText;
};