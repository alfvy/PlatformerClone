#include "Headers.h"

#pragma once

class Map;

class Entity
{
public:
	sf::RectangleShape rect;
	sf::Vector2f vel;

	float speed;

	// true = right, false = left
	bool direction;
	bool alive;

	void draw(sf::RenderWindow* window);
	void physicsUpdate(float deltaTime, Map map, bool debug);

	Entity(int x, int y, int width, int height, sf::Color color, float speed);
	Entity();
	~Entity();
};

class Player : public Entity
{
public:
	Player(int x, int y, int width, int height, sf::Color color, float speed);
	void draw(sf::RenderWindow* window);
	void physicsUpdate(float deltaTime, Map map, bool debug);
	Player();
	~Player();
};