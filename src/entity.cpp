#include "Entity.hpp"
#include "Math.hpp"

Entity::Entity()
	: velocity(sf::Vector2f(0, 0))
{
}

Entity::Entity(sf::Texture &texture)
	: sf::Sprite(texture), velocity(sf::Vector2f(0, 0))
{
}

void Entity::update(sf::Vector2i windowSize)
{
	if (getPosition().x > windowSize.x)
		setPosition(0, getPosition().y);
	else if (getPosition().x < 0)
		setPosition(windowSize.x, getPosition().y);
	if (getPosition().y > windowSize.y)
	{
		velocity.y = 0;
		setPosition(getPosition().x, windowSize.y);
	}
	else if (getPosition().y < 0)
	{
		velocity.y = 0;
		setPosition(getPosition().x, 0);
	}

	move(velocity.x, velocity.y);
}

void Entity::launch(float magnitude, float angle)
{
	float rads = radians(angle);

	velocity.x += magnitude * cos(rads);
	velocity.y += magnitude * sin(rads);
}

void Entity::setVelocity(sf::Vector2f &p_velocity)
{
	velocity.x = p_velocity.x;
	velocity.y = p_velocity.y;
}

void Entity::setVelocity(float x, float y)
{
	velocity.x = x;
	velocity.y = y;
}

sf::Vector2f const &Entity::getVelocity() const
{
	return velocity;
}