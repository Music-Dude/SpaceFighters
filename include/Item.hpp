#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>

class Item : sf::Sprite
{
public:
	Item(const std::string &name, sf::Texture &texture);

private:
	std::string name;
};

struct ItemStack
{
	Item item;
	size_t count;
};

#endif /* ITEM_H */