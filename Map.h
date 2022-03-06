#include "Headers.h"

#pragma once

class Entity;
class Player;

enum class CollisionDirection : int {
	none = 0, top = 1, bottom = 2, left = 3, right = 4
};

// block class inheriting from the shape class to not replace a lot of code
class Block : public sf::RectangleShape
{
public:
	// current distance to the player
	int distanceToPlayer;
	// for bulk updates
	void updatePlayerDistance(sf::RectangleShape shape);

	bool operator<(Block *other) const;
	bool operator>(const Block& other) const;
};

class Map
{
public:
	// image holding map information
	sf::Image mapImage;
	// vector holding all the blocks to render
	std::vector<Block*> map;
	// vector holding possible enemies/entities
	std::vector<Entity*> *entities;
	// pointer to the render window for debug purposes
	sf::RenderWindow* window;

	// function to read from the passed image and construct the map vector
	void render();
	// update all the block's distance to the player
	void updateBlocks(Player player);

	// collision detection past the basic sfml intersect function
	CollisionDirection checkCollisionDirection(sf::RectangleShape r1, sf::RectangleShape r2, bool debug = true);

	// class responsible for holding the information of an image, and transforming that image into a vector of "blocks"
	Map(sf::Image Image, sf::RenderWindow *window);
	~Map();
};