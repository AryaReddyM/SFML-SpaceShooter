#pragma once

#include "Bullet.h"
#include <vector>;

class BulletHandler {
public:
	void AddBullet(sf::Vector2f pos);
	void UpdateBullets(sf::RenderWindow& window);
	void DestroyBullets();

	std::vector<Bullet> bullets;
};