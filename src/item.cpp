#include "Item.hpp"

Item::Item(const std::string &name, sf::Texture &texture) : sf::Sprite(texture), name(name)
{
}