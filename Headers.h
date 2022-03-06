#include <cstdio>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <functional>
#include <iostream>
#include <chrono>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

int const GAME_SCALE = 32;
#define uint unsigned int;
float const gravity = 5.4f;

//const sf::Color winningColor(255, 255, 95, 0);

#pragma once

// static utility class for global functions and variables
static class util
{
public:
	// to calculate the distance between the center of 2 objects
	static unsigned int distanceToCenter(sf::FloatRect obj1, sf::FloatRect obj2)
	{
		float x1, x2, y1, y2, w1, w2, h1, h2, c1x, c1y, c2x, c2y, distance;

		x1 = obj1.left;
		y1 = obj1.top;
		w1 = obj1.width;
		h1 = obj1.height;

		x2 = obj2.left;
		y2 = obj2.top;
		w2 = obj2.width;
		h2 = obj2.height;

		c1x = x1 + (w1 * 0.5f);
		c1y = y1 + (h1 * 0.5f);

		c2x = x2 + (w2 * 0.5f);
		c2y = y2 + (h2 * 0.5f);

		float xdistance = c2x - c1x;
		float ydistance = c2y - c1y;

		distance = ::sqrt((xdistance * xdistance) + (ydistance * ydistance));

		return unsigned int(distance);
	}

	// length of a quad's diagonal
	static float diagonalLength(sf::FloatRect rect)
	{
		return std::sqrt(((rect.width) * (rect.width)) + ((rect.height) * (rect.height)));
	}
};