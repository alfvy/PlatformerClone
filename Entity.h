#include "Headers.h"

#pragma once

class Map;

// base entity class for dynamic objects with physics calculations
class Entity
{
public:
	// the actual shape of the object with all the information pretaining to how its drawn
	sf::RectangleShape rect;
	// the object's imediate velocity
	sf::Vector2f vel;

	float speed;

	// true = right, false = left
	bool direction;
	// to save on computations if the entity is dead
	bool alive;

	// drawing the actual object using a refrence to the window
	void draw(sf::RenderWindow* window);
	// all the actual calculations that are needed to make the entity functions
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