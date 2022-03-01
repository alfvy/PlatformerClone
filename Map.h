#include "Headers.h"

#pragma once

class Entity;

enum class CollisionDirection : int {
	none = 0, top = 1, bottom = 2, left = 3, right = 4
};


class Map
{
public:
	// image holding map information
	sf::Image mapImage;
	// vector holding all the blocks to render
	std::vector<sf::RectangleShape*> map;
	// vector holding possible enemies/entities
	std::vector<Entity*> *entities;
	// pointer to the render window for debug purposes
	sf::RenderWindow* window;

	// function to read from the passed image and construct the map vector
	void render();

	// collision detection past the basic sfml intersect function
	CollisionDirection checkCollisionDirection(sf::RectangleShape r1, sf::RectangleShape r2, bool debug = true);

	// class responsible for holding the information of an image, and transforming that image into a vector of "blocks"
	Map(sf::Image Image, sf::RenderWindow *window);
	~Map();
};