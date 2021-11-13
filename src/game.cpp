#include "Game.hpp"

Game::Game()
	: m_windowSize(800, 600), m_window(sf::VideoMode(m_windowSize.x, m_windowSize.y), "Space Fighters", sf::Style::None)
{
	m_window.setFramerateLimit(165);
	m_window.setVerticalSyncEnabled(true);

	bgSprite.setTextureRect(sf::IntRect(0, 0, m_windowSize.x, m_windowSize.y));
	player.setPosition(m_windowSize.x / 3, m_windowSize.y / 2);
	clickToPlay.setPosition((m_windowSize.x / 2) - (clickToPlay.getGlobalBounds().width / 2), m_windowSize.y - (clickToPlay.getGlobalBounds().height * 2));
}

void Game::run()
{
	m_state = GameState::Title;

	while (m_window.isOpen())
	{
		switch (m_state)
		{
		case GameState::Title:
			title();
			break;
		case GameState::Play:
			play();
			break;
		case GameState::Pause:
			// TODO: implement pause
			break;
		case GameState::GameOver:
			gameOver();
			break;
		}
	}
}

void Game::gameOver()
{
	titleText.setPosition(sin(m_clock.getElapsedTime().asSeconds()) * 50 + (m_windowSize.x / 2) - titleText.getGlobalBounds().width / 2,
						  sin(m_clock.getElapsedTime().asSeconds() * 2) * 30 + titleText.getGlobalBounds().height);

	m_window.draw(bgSprite);
	m_window.draw(killer);
	m_window.draw(player);
	m_window.draw(titleText);

	if (sin(m_clock.getElapsedTime().asSeconds() * 4) > 0.2)
		m_window.draw(clickToPlay);

	m_window.display();

	while (m_window.pollEvent(m_event))
	{
		switch (m_event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;
		case sf::Event::MouseButtonReleased:
			// reset player
			player.setPosition(m_windowSize.x / 3, m_windowSize.y / 2);

			// lower opacity means motion blur
			bgSprite.setColor(sf::Color(0xffffff55));
			m_state = GameState::Play;

			return;

		default:
			break;
		}
	}
}

void Game::title()
{
	titleText.setPosition(sin(m_clock.getElapsedTime().asSeconds()) * 40 + (m_windowSize.x / 2) - titleText.getGlobalBounds().width / 2,
						  sin(m_clock.getElapsedTime().asSeconds() * 2) * 30 + titleText.getGlobalBounds().height);

	m_window.draw(bgSprite);
	m_window.draw(titleText);

	if (sin(m_clock.getElapsedTime().asSeconds() * 4) > 0.2)
		m_window.draw(clickToPlay);

	m_window.display();

	while (m_window.pollEvent(m_event))
	{
		switch (m_event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;
		case sf::Event::MouseButtonReleased:
			// lower opacity means motion blur
			bgSprite.setColor(sf::Color(0xffffff55));

			m_state = GameState::Play;
			return;
		default:
			break;
		}
	}
}

void Game::play()
{
	while (m_window.pollEvent(m_event))
	{
		switch (m_event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;
		default:
			break;
		}
	}

	m_mouse = sf::Mouse::getPosition(m_window);

	// Rotate player to face mouse
	player.setRotation(degrees(atan2(m_mouse.y - player.getPosition().y, m_mouse.x - player.getPosition().x)) + 90);

	// Chance to spawn astroids
	if (!(rand() % 100))
	{
		astroid1.setPosition(rand() % m_windowSize.x, 1);
		astroid1.setVelocity(rand() % 10, (rand() % 10) / 10 + 1);
		astroids.push_back(astroid1);
	}
	if (!(rand() % 175))
	{
		astroid2.setPosition(rand() % m_windowSize.x, 1);
		astroid2.setVelocity(rand() % 10, (rand() % 10) / 10 + 1);
		astroids.push_back(astroid2);
	}

	// limit shooting to 10/s
	if (m_clock.getElapsedTime().asSeconds() > 0.1 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		bullet.setPosition(player.getPosition().x - bullet.getGlobalBounds().width / 2, player.getPosition().y - bullet.getGlobalBounds().height / 2);
		bullet.setVelocity(0, 0);
		bullet.launch(8, player.getRotation() - 90);
		bullets.push_back(bullet);
		m_clock.restart();
	}

	// Keyboard movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		player.launch(0.2, 270);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		player.launch(0.2, 180);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		player.launch(0.2, 90);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		player.launch(0.2, 0);

	player.update(m_windowSize);

	m_window.draw(bgSprite);

	for (auto astr = astroids.begin(); astr != astroids.end();)
	{
		astr->update(m_windowSize);

		// player touched astroid, game over
		if (astr->getGlobalBounds().intersects(player.getGlobalBounds()))
		{
			killer = *astr;

			player.setVelocity(0, 0);

			// change messages
			titleText.setString("Game over!");
			clickToPlay.setString("Click to play again");
			clickToPlay.setCharacterSize(40U);
			clickToPlay.setPosition((m_windowSize.x / 2) - (clickToPlay.getGlobalBounds().width / 2), m_windowSize.y - (clickToPlay.getGlobalBounds().height * 2));

			clickToPlay.setFillColor(sf::Color(0xaaaaaaee));
			clickToPlay.setOutlineColor(sf::Color(0x777777aa));

			// clear vectors and free memory
			astroids.clear();
			astroids.shrink_to_fit();

			bullets.clear();
			bullets.shrink_to_fit();

			// increase motion blur
			bgSprite.setColor(sf::Color(0xffffff22));

			m_state = GameState::GameOver;
			return;
		}
		else if (astr->getGlobalBounds().left > m_windowSize.x || astr->getGlobalBounds().left < 0 || astr->getGlobalBounds().top > m_windowSize.y || astr->getGlobalBounds().top < 0)
			astroids.erase(astr);
		else
		{
			m_window.draw(*astr);
			astr++;
		}
	}

	for (auto bull = bullets.begin(); bull != bullets.end();)
	{
		bull->update(m_windowSize);

		if (bull->getGlobalBounds().left > m_windowSize.x || bull->getGlobalBounds().left < 0 || bull->getGlobalBounds().top > m_windowSize.y || bull->getGlobalBounds().top < 0)
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

		m_window.draw(*bull);

		bull++;
		continue;

	delBullet:
		bullets.erase(bull);
	}

	m_window.draw(player);
	m_window.display();
}