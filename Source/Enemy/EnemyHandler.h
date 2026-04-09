#pragma once

#include "Enemy.h"
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>

class EnemyHandler {
public:
	EnemyHandler(sf::RenderWindow& window);
	void AddEnemy(sf::Vector2f pos);
	void UpdateEnemies();
	void HandleWaves();
	void StartNewWave();

	sf::Texture texture;
	std::vector<Enemy> enemies;
	sf::RenderWindow* window;

	int wave = 0;
	int enemyWaveNum = 55;

	sf::Vector2f startPos = { -200.0f, -300.0f };
};