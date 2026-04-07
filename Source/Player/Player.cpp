#include "Player.h"
#include <iostream>

Player::Player(sf::Vector2f startPos) : ship(icon) {
    if (!icon.loadFromFile("Assets/SpaceShip.png")) {
        std::cerr << "No Image \n";
    }

    ship.setTexture(icon, true);
    ship.setScale({ 0.7f, 0.7f });

    ship.setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });

    pos = startPos;
    ship.setPosition(pos);
}

void Player::Draw(sf::RenderWindow& window) {
	window.draw(ship);
}

void Player::Move() {
	ship.setPosition(pos);

	pos += vel;

    sf::FloatRect bounds = ship.getGlobalBounds();
}

void Player::ChangeXDir(float dirX) {
	vel.x += (speed * dirX);
}

void Player::ChangeYDir(float dirY) {
	vel.y += (speed * dirY);
}
