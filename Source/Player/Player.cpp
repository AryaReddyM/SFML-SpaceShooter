#include "Player.h"
#include <iostream>

Player::Player(sf::Vector2f startPos, sf::RenderWindow& window) : ship(icon), window(window) {
    if (!icon.loadFromFile("Assets/SpaceShip.png")) {
        std::cerr << "No Image \n";
    }

    ship.setTexture(icon, true);
    ship.setScale({ 0.7f, 0.7f });

    bounds = ship.getGlobalBounds();
    ship.setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });

    pos = startPos;
    ship.setPosition(pos);
}

void Player::Draw() {
	window.draw(ship);
}

void Player::Move() {
    bounds = ship.getGlobalBounds();

	ship.setPosition(pos);

    if (!OutOfBounds()) {
        pos += vel;
    }
}

void Player::ChangeXDir(float dirX) {
	vel.x += (speed * dirX);
}

void Player::ChangeYDir(float dirY) {
	vel.y += (speed * dirY);
}

bool Player::OutOfBounds() {
    if (pos.y < 0) {
        pos.y += 5;
        return true;
    }

    if ((pos.y) > window.getSize().y) {
        pos.y -= 5;
        return true;
    }

    if (pos.x < 0) {
        pos.x += 5;
        return true;
    }

    if ((pos.x + bounds.size.x) > window.getSize().x) {
        pos.x -= 5;
        return true;
    }

    return false;
}
