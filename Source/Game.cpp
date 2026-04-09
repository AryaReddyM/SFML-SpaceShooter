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

	if (!font.openFromFile("Assets/arial.ttf")) { std::cerr << "Did not load font \n"; }

	waveText = std::make_unique<sf::Text>(font, "Wave: ", 48);
	waveText->setFillColor(sf::Color::White);
	waveText->setPosition({ 100.f, (float)window.getSize().y - 100.f });

	gameOverText = std::make_unique<sf::Text>(font, "GAME OVER", 80);
	gameOverText->setFillColor(sf::Color::Red);
	gameOverText->setPosition({ (float)window.getSize().x / 2 - 175.0f, (float)window.getSize().y / 2 });

	player = new Player(sf::Vector2f((float)window.getSize().x / 2, (float)window.getSize().y / 2), window);
	bullet = new BulletHandler();
	enemy = new EnemyHandler(window);

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		window.clear(sf::Color(18, 0, 92));

		if (!gameOver) {
			player->vel = sf::Vector2f(0.f, 0.f);
			HandleInput();
			HandleCollisions();

			player->Move();
			bullet->UpdateBullets(window);
			enemy->UpdateEnemies();
			enemy->HandleWaves();

			waveText->setString("Wave: " + std::to_string(enemy->wave));
			gameOverText->setScale({ 0.0f, 0.0f });
		}

		player->Draw();
		for (auto& b : bullet->bullets) b.Draw(window);
		for (auto& e : enemy->enemies) e.Draw();
		window.draw(*waveText);
		window.draw(*gameOverText);

		HandleGameOver();
		
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

		if (bullet->bullets.size() < 1 && (time.asSeconds() - lastTime > 0.2f)) {
			bullet->AddBullet({ player->pos.x + 10.0f, player->pos.y });
			lastTime = time.asSeconds();
		}
	}
}

void Game::HandleCollisions() {
	for (int i = 0; i < enemy->enemies.size(); i++) {
		for (int j = 0; j < bullet->bullets.size(); j++) {
			if (enemy->enemies[i].bounds.findIntersection(bullet->bullets[j].bounds)) {
				enemy->enemies[i].shouldDie = true;
				bullet->bullets[j].shouldDestroy = true;
			}
		}
	}
}

void Game::HandleGameOver() {
	if (!gameOver) {
		for (int i = 0; i < enemy->enemies.size(); i++) {
			if (enemy->enemies[i].bounds.findIntersection(player->bounds) ||
				enemy->enemies[i].pos.y > window.getSize().y) {

				gameOver = true;
				gameOverText->setScale({ 1.0f, 1.0f });
				gameOverTime = clock.getElapsedTime().asSeconds();
				return;
			}
		}
	}
	else {
		if (clock.getElapsedTime().asSeconds() - gameOverTime > restartDelay) {
			Reset();
		}
	}
}

void Game::Reset() {
	delete player;
	delete bullet;
	delete enemy;

	player = new Player(sf::Vector2f((float)window.getSize().x / 2, (float)window.getSize().y / 2), window);
	bullet = new BulletHandler();
	enemy = new EnemyHandler(window);

	lastTime = clock.getElapsedTime().asSeconds();
	gameOver = false;
}
