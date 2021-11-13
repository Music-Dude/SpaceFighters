#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "Math.hpp"
#include "Game.hpp"

int main()
{
	srand(time(NULL));

	bgTexture.loadFromFile("assets/png/bg.png");
	bgTexture.setRepeated(true);

	// Draw background across whole screen, repeating it
	// TODO: Moving background
	bgSprite.setTexture(bgTexture);
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

	titleText.setFillColor(sf::Color(0xfff2b2ff));
	titleText.setOutlineColor(sf::Color(0xd3c998ff));
	titleText.setOutlineThickness(4);
	titleText.setString("Space Fighters");
	titleText.setFont(font);
	titleText.setCharacterSize(72U);

	clickToPlay.setFillColor(sf::Color(0xffffefff));
	clickToPlay.setOutlineColor(sf::Color(0xffffff88));
	clickToPlay.setOutlineThickness(2);
	clickToPlay.setString("Click to play");
	clickToPlay.setFont(font);
	clickToPlay.setCharacterSize(50U);

	Game game;
	game.run();

	return 0;
}
