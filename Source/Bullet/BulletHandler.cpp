#include "BulletHandler.h"
#include <iostream>

void BulletHandler::AddBullet(sf::Vector2f pos) {
	Bullet bullet = Bullet(pos);

	bullets.push_back(bullet);
}

void BulletHandler::UpdateBullets(sf::RenderWindow& window) {
	for (int i = 0; i < bullets.size(); i++) {
		bullets[i].Draw(window);
		bullets[i].Move();
	}

	bullets.erase(
		std::remove_if(bullets.begin(), bullets.end(),
			[](Bullet& b) { return b.OutOfBounds() || b.shouldDestroy; }),
		bullets.end()
	);
}