#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity : public sf::Sprite
{
public:
	Entity(sf::Texture &texture);
	Entity();

	// Move player according to velocity
	void update(sf::Vector2u windowSize);

	/// \brief Set corresponding x and y velocities given and angle and power
	/// \param magnitude Power to scale velocities with
	/// \param angle     Angle, in degrees to determine velocities from
	void launch(float magnitude, float angle);

	// Directly set velocity values
	void setVelocity(sf::Vector2f &velocity);
	void setVelocity(float x, float y);

	// Get the player's velocity
	sf::Vector2f const &getVelocity() const;

private:
	sf::Vector2f velocity;
};

#endif /* ENTITY_H */