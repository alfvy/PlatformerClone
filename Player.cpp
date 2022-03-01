#include "Player.h"

Player::Player(int x, int y)
{
	sf::Texture texture;
	texture.loadFromFile("res\\sprites\\RoundedRect.png");

	this->setTexture(texture);
	this->setPosition(x, y);
}

sf::Vector2f Player::pos()
{
	return sf::Vector2f(this->getPosition().x, this->getPosition().y);
}