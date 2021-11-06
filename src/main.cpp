#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "Math.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

sf::Texture bgTexture, playerTexture, bulletTexture, astroid1Texture, astroid2Texture;
sf::Font font;
sf::Clock clck;

Entity bgSprite, player, bullet, astroid1, astroid2;
std::vector<Entity> astroids, bullets;
Entity killer;
Mouse mouse;

sf::Vector2i windowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

sf::Text titleText("Space Fighters", font, 72U),
	clickToPlay("Click to play", font, 50U);

enum class GameState
{
	Title,
	Play,
	Pause,
	GameOver
};

void gameOver(sf::RenderWindow &window, sf::Event &ev, GameState &state)
{
	titleText.setPosition(sin(clck.getElapsedTime().asSeconds()) * 60 + (windowSize.x / 2) - titleText.getGlobalBounds().width / 2, sin(clck.getElapsedTime().asSeconds() * 2) * 40 + titleText.getGlobalBounds().height);
	window.draw(bgSprite);
	window.draw(killer);
	window.draw(player);
	window.draw(titleText);

	if (sin(clck.getElapsedTime().asSeconds() * 4) > 0.2)
		window.draw(clickToPlay);

	window.display();

	while (window.pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseButtonReleased:
			// reset player
			player.setPosition(windowSize.x / 3, windowSize.y / 2);

			// lower opacity means motion blur
			bgSprite.setColor(sf::Color(0xffffff55));
			state = GameState::Play;
			return;
		default:
			break;
		}
	}
}

void title(sf::RenderWindow &window, sf::Event &ev, GameState &state)
{
	titleText.setPosition(sin(clck.getElapsedTime().asSeconds()) * 50 + (windowSize.x / 2) - titleText.getGlobalBounds().width / 2, sin(clck.getElapsedTime().asSeconds() * 2) * 40 + titleText.getGlobalBounds().height);

	window.draw(bgSprite);
	window.draw(titleText);

	if (sin(clck.getElapsedTime().asSeconds() * 4) > 0.2)
		window.draw(clickToPlay);

	window.display();

	while (window.pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseButtonReleased:
			// lower opacity means motion blur
			bgSprite.setColor(sf::Color(0xffffff55));
			state = GameState::Play;
			return;
		default:
			break;
		}
	}
}

void play(sf::RenderWindow &window, sf::Event &ev, GameState &state)
{
	while (window.pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseButtonPressed:
			if (ev.mouseButton.button == sf::Mouse::Left)
				mouse.lDown = true;
			if (ev.mouseButton.button == sf::Mouse::Right)
				mouse.rDown = true;
			break;
		case sf::Event::MouseButtonReleased:
			if (ev.mouseButton.button == sf::Mouse::Left)
				mouse.lDown = false;
			if (ev.mouseButton.button == sf::Mouse::Right)
				mouse.rDown = false;
			break;
		case sf::Event::MouseMoved:
			mouse.x = ev.mouseMove.x;
			mouse.y = ev.mouseMove.y;
			break;
		default:
			break;
		}
	}

	// Rotate player to face mouse
	player.setRotation(degrees(atan2(mouse.y - player.getPosition().y, mouse.x - player.getPosition().x)) + 90);

	// Chance to spawn astroids
	if (!(rand() % 100))
	{
		astroid1.setPosition(rand() % windowSize.x, 1);
		astroid1.setVelocity(rand() % 10, (rand() % 10) / 10 + 1);
		astroids.push_back(astroid1);
	}
	if (!(rand() % 175))
	{
		astroid2.setPosition(rand() % windowSize.x, 1);
		astroid2.setVelocity(rand() % 10, (rand() % 10) / 10 + 1);
		astroids.push_back(astroid2);
	}

	// limit shooting to 10/s
	if (clck.getElapsedTime().asSeconds() > 0.1 && mouse.lDown)
	{
		bullet.setPosition(player.getPosition().x - bullet.getGlobalBounds().width / 2, player.getPosition().y - bullet.getGlobalBounds().height / 2);
		bullet.setVelocity(0, 0);
		bullet.launch(8, player.getRotation() - 90);
		bullets.push_back(bullet);
		clck.restart();
	}

	// Keyboard movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		player.launch(0.2, 270);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		player.launch(0.2, 180);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		player.launch(0.2, 90);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		player.launch(0.2, 0);

	player.update(windowSize);

	window.draw(bgSprite);

	for (auto astr = astroids.begin(); astr != astroids.end();)
	{
		astr->update(windowSize);

		// player touched astroid, game over
		if (astr->getGlobalBounds().intersects(player.getGlobalBounds()))
		{
			killer = *astr;

			state = GameState::GameOver;

			player.setVelocity(0, 0);

			// change messages
			titleText.setString("Game over!");
			clickToPlay.setString("Click to play again");

			clickToPlay.setFillColor(sf::Color(0xaaaaaaee));
			clickToPlay.setOutlineColor(sf::Color(0x777777aa));

			// clear vectors and free memory
			astroids.clear();
			astroids.shrink_to_fit();

			bullets.clear();
			bullets.shrink_to_fit();

			clickToPlay.setPosition((windowSize.x / 2) - (clickToPlay.getGlobalBounds().width / 2), windowSize.y - (clickToPlay.getGlobalBounds().height * 4));

			// increase motion blur
			bgSprite.setColor(sf::Color(0xffffff22));

			return;
		}
		else if (astr->getGlobalBounds().left > windowSize.x || astr->getGlobalBounds().left < 0 || astr->getGlobalBounds().top > windowSize.y || astr->getGlobalBounds().top < 0)
			astroids.erase(astr);
		else
		{
			window.draw(*astr);
			astr++;
		}
	}

	for (auto bull = bullets.begin(); bull != bullets.end();)
	{
		bull->update(windowSize);

		if (bull->getGlobalBounds().left > windowSize.x || bull->getGlobalBounds().left < 0 || bull->getGlobalBounds().top > windowSize.y || bull->getGlobalBounds().top < 0)
			goto delBullet;

		for (auto astr = astroids.begin(); astr != astroids.end();)
		{
			if (bull->getGlobalBounds().intersects(astr->getGlobalBounds()))
			{
				astroids.erase(astr);
				goto delBullet;
			}
			else
				astr++;
		}

		window.draw(*bull);

		bull++;
		continue;

	delBullet:
		bullets.erase(bull);
	}

	window.draw(player);
	window.display();
}

void game(sf::RenderWindow &window, sf::Event &ev, GameState state)
{
	switch (state)
	{
	case GameState::Play:
		play(window, ev, state);
		break;
	case GameState::Title:
		title(window, ev, state);
		break;
	case GameState::GameOver:
		gameOver(window, ev, state);
	default:
		break;
	}

	if (window.isOpen())
		game(window, ev, state);
}

int main()
{
	srand(time(NULL));

	bgTexture.loadFromFile("assets/png/bg.png");
	bgTexture.setRepeated(true);

	// Draw background across whole screen, repeating it
	// TODO: Moving background
	bgSprite.setTexture(bgTexture);
	bgSprite.setTextureRect(sf::IntRect(0, 0, windowSize.x, windowSize.y));
	bgSprite.scale(2, 2);

	playerTexture.loadFromFile("assets/png/player.png");

	astroid1Texture.loadFromFile("assets/png/astroid1.png");
	astroid2Texture.loadFromFile("assets/png/astroid2.png");
	bulletTexture.loadFromFile("assets/png/bullet.png");

	font.loadFromFile("assets/ttf/light_pixel-7.ttf");

	astroid1.setTexture(astroid1Texture);
	astroid1.setScale(2, 2);
	astroid2.setTexture(astroid2Texture);
	astroid2.setScale(2, 2);

	bullet.setTexture(bulletTexture);

	player.setTexture(playerTexture);
	player.setScale(2, 2);
	player.setOrigin(playerTexture.getSize().x / 2, playerTexture.getSize().y / 2);
	player.setPosition(windowSize.x / 3, windowSize.y / 2);

	titleText.setFillColor(sf::Color(0xfff2b2ff));
	titleText.setOutlineColor(sf::Color(0xd3c998ff));
	titleText.setOutlineThickness(4);

	clickToPlay.setPosition((windowSize.x / 2) - (clickToPlay.getGlobalBounds().width / 2), windowSize.y - (clickToPlay.getGlobalBounds().height * 2));
	clickToPlay.setFillColor(sf::Color(0xffffefff));
	clickToPlay.setOutlineColor(sf::Color(0xffffff88));
	clickToPlay.setOutlineThickness(2);

	// Create non resizable window
	sf::RenderWindow screen(sf::VideoMode(windowSize.x, windowSize.y), "Space Fighters", sf::Style::None);
	sf::Event ev;

	screen.setFramerateLimit(165);
	screen.setVerticalSyncEnabled(true);

	game(screen, ev, GameState::Title);

	return 0;
}
