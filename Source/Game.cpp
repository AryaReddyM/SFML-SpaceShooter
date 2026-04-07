#include "Game.h"
#include "Windows.h"
#include <iostream>

int main() {
	Game game = Game();

	return 0;
}

Game::Game() {
	window = sf::RenderWindow(sf::VideoMode({ res.x, res.y }), "Space Shooter");

	HWND handle = window.getNativeHandle();
	ShowWindow(handle, SW_MAXIMIZE);

	window.setView(sf::View(sf::FloatRect({ 0.f, 0.f }, { (float)window.getSize().x, (float)window.getSize().y })));

	player = new Player(sf::Vector2f(float(window.getSize().x / 2), float(window.getSize().y / 2)));
	bullet = new BulletHandler();

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		player->vel = sf::Vector2f(0.f, 0.f);
		HandleInput();

		window.clear(sf::Color(18, 0, 92));

		player->Move();
		player->Draw(window);

		bullet->UpdateBullets(window);

		window.display();
	}
}

void Game::HandleInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
		player->ChangeYDir(-1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
		player->ChangeYDir(1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
		player->ChangeXDir(1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
		player->ChangeXDir(-1);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
		sf::Time time = clock.getElapsedTime();

		if (time.asSeconds() - lastTime > shotCooldown) {
			bullet->AddBullet({ player->pos.x + 45.0f, player->pos.y });
			lastTime = time.asSeconds();
		}
	}
}