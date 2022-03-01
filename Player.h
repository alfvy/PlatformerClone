#include "Headers.h"

#pragma once

class Player : public sf::Sprite
{
public:
	// returns player's current positions
	sf::Vector2f pos();
	// returns player's current size
	sf::Vector2f size();

	Player(int x, int y);
	~Player();

	void Move(sf::Vector2f moveVector);
};