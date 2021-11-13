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
	void run();

private:
	sf::Vector2u m_windowSize;
	sf::RenderWindow m_window;
	sf::Event m_event;
	sf::Clock m_clock;
	Mouse m_mouse;
	std::vector<Entity> m_astroids, m_bullets;

	// Advance to the next frame, checking state and events
	void frame();

	// Game state functions
	void title();
	void play();
	void gameOver();
};

#endif /* GAME_H */