#include "Enemy.h"
#include <iostream>

Enemy::Enemy(sf::Vector2f pos, sf::RenderWindow& window, const sf::Texture& texture) : window(&window), ship(texture) {
	ship.setTexture(texture, true);
	ship.setScale({ 0.7f, 0.7f });

	sf::FloatRect b = ship.getLocalBounds();
	ship.setOrigin({ b.size.x / 2.f, b.size.y / 2.f });

	this->pos = pos;
}

void Enemy::Draw() {
	window->draw(ship);
}

void Enemy::Move() {
	bounds = ship.getGlobalBounds();

	pos.x += speed * dir;

	if (pos.x < 0) {
		pos.x = 0;
		pos.y += 100.0f;
		dir = 1;
	}
	else if (pos.x > window->getSize().x) {
		pos.x = window->getSize().x;
		pos.y += 100.0f;
		dir = -1;
	}

	ship.setPosition(pos);
}

bool Enemy::OutOfBounds() {
	return (pos.y > window->getSize().y + 100.0f);
}

bool Enemy::Shot(sf::FloatRect otherBounds) {
	auto intersect = bounds.findIntersection(otherBounds);
	if (intersect) {
		return true;
	}
	return false;
}
