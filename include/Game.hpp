#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Math.hpp"

static sf::Texture bgTexture, playerTexture, bulletTexture, astroid1Texture, astroid2Texture;
static sf::Font font;

inline Entity bgSprite, player, bullet, astroid1, astroid2, killer;
inline std::vector<Entity> astroids, bullets;
inline sf::Text titleText, clickToPlay;

enum class GameState
{
	Title,
	Play,
	Pause,
	GameOver
};

class Game
{
public:
	Game();

	// Start main loop
	void run();

private:
	sf::Vector2u m_windowSize;
	sf::RenderWindow m_window;
	sf::Event m_event;
	sf::Clock m_clock;
	GameState m_state;
	sf::Vector2i m_mouse;
	std::vector<Entity> m_astroids, m_bullets;

	// Game state functions
	void title();
	void play();
	void gameOver();
};

#endif /* GAME_H */