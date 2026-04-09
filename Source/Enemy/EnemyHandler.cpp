#include "EnemyHandler.h"
#include <iostream>

EnemyHandler::EnemyHandler(sf::RenderWindow& window) : window(&window) {
	if (!texture.loadFromFile("Assets/EnemyShip.png")) {
		std::cerr << "Failed to load enemy texture\n";
	}
}

void EnemyHandler::AddEnemy(sf::Vector2f pos) {
	Enemy enemy = Enemy(pos, *window, texture);

	enemies.push_back(enemy);
}

void EnemyHandler::UpdateEnemies() {
	float speedMultiplier = 1.0f + (float)(enemyWaveNum - enemies.size()) * 0.01f;

	for (int i = 0; i < enemies.size(); i++) {
		float originalSpeed = enemies[i].speed;
		enemies[i].speed *= speedMultiplier;

		enemies[i].Move();
		enemies[i].Draw();

		enemies[i].speed = originalSpeed;	
	}

	enemies.erase(
		std::remove_if(enemies.begin(), enemies.end(),
			[](Enemy& e) { return e.OutOfBounds() || e.shouldDie; }),
		enemies.end()
	);
}

void EnemyHandler::HandleWaves() {
	if (enemies.size() <= 0) {
		StartNewWave();
	}
}

void EnemyHandler::StartNewWave() {
	float currentStartY = startPos.y + (wave * 30.0f);
	if (currentStartY > 400.0f) currentStartY = 400.0f;

	int columns = 11;
	int rows = 5;
	float xSpacing = 130.0f;
	float ySpacing = 100.0f;

	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			sf::Vector2f pos;
			pos.x = 100.0f + (c * xSpacing);
			pos.y = currentStartY + (r * ySpacing);

			AddEnemy(pos);
		}
	}

	wave++;
}