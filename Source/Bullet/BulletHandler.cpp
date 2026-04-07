#include "BulletHandler.h"

void BulletHandler::AddBullet(sf::Vector2f pos) {
	Bullet bullet = Bullet(pos);

	bullets.push_back(bullet);
}

void BulletHandler::UpdateBullets(sf::RenderWindow& window) {
	for (int i = 0; i < bullets.size(); i++) {
		bullets[i].Draw(window);
		bullets[i].Move();
	}
}

void BulletHandler::DestroyBullets() {
	std::vector<Bullet> temp = bullets;

	for (int i = 0; i < bullets.size(); i++) {
		if (true) { // Change to when bullet should be destroyed
			temp.erase(temp.begin() + i);
		}
	}

	bullets = temp;
}