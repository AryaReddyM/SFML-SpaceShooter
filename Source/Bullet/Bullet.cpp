#include "Bullet.h"

Bullet::Bullet(sf::Vector2f pos) {
	this->pos = pos;

	proj.setFillColor(sf::Color::Red);
	proj.setSize({ 15.0f, 30.0f });
		
	proj.setOrigin({ proj.getSize().x / 2.0f, proj.getSize().y / 2.0f });
}

void Bullet::Draw(sf::RenderWindow& window) {
	window.draw(proj);
}

void Bullet::Move() {
	proj.setPosition(pos);

	pos.y -= speed;

	bounds = proj.getGlobalBounds();
}
