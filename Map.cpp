#include "Map.h"
#include "Entity.h"

Map::Map(sf::Image image, sf::RenderWindow *window)
{
	this->window = window;
	this->mapImage = image;	
	this->entities = new std::vector<Entity*>;
}

void Map::render()
{
	for (int i = 0; i < this->mapImage.getSize().x; i++)
	{
		for (int j = 0; j < this->mapImage.getSize().y; j++)
		{
			if (mapImage.getPixel(i, j) == sf::Color::White)
			{
				sf::RectangleShape* newRect = new sf::RectangleShape;
				newRect->setPosition(i * GAME_SCALE, j * GAME_SCALE);
				newRect->setSize(sf::Vector2f(GAME_SCALE, GAME_SCALE));
				newRect->setFillColor(sf::Color::Transparent);
				map.push_back(newRect);
			}

			if (mapImage.getPixel(i, j) == sf::Color::Black)
			{
				sf::RectangleShape* newRect = new sf::RectangleShape;
				newRect->setPosition(i * GAME_SCALE, j * GAME_SCALE);
				newRect->setSize(sf::Vector2f(GAME_SCALE, GAME_SCALE));
				newRect->setFillColor(sf::Color::Black);
				map.push_back(newRect);
			}

			if (mapImage.getPixel(i, j) == sf::Color(255, 255, 95))
			{
				sf::RectangleShape* newRect = new sf::RectangleShape;
				newRect->setPosition(i * GAME_SCALE, j * GAME_SCALE);
				newRect->setSize(sf::Vector2f(GAME_SCALE, GAME_SCALE));
				newRect->setFillColor(sf::Color(255, 255, 95));
				map.push_back(newRect);
			}

			if (mapImage.getPixel(i, j) == sf::Color::Red)
			{
				Entity* newEntity = new Entity;
				newEntity->rect.setPosition(i * GAME_SCALE, j * GAME_SCALE);
				newEntity->rect.setSize(sf::Vector2f(GAME_SCALE, GAME_SCALE));
				newEntity->rect.setFillColor(sf::Color::Red);
				newEntity->vel = sf::Vector2f(0, 0);
				newEntity->direction = true;
				newEntity->speed = 120.f;
				newEntity->alive = true;
				entities->push_back(newEntity);
			}
		}
	}
}

CollisionDirection Map::checkCollisionDirection(sf::RectangleShape r1, sf::RectangleShape r2, bool debug)
{
	CollisionDirection overlap = CollisionDirection::none;

	if (r1.getGlobalBounds().intersects(r2.getGlobalBounds())) {
		float playerX = r1.getPosition().x;
		float playerY = r1.getPosition().y;
		float objX = r2.getPosition().x;
		float objY = r2.getPosition().y;

		float playerBottom = playerY + r1.getLocalBounds().height;
		float objBottom = objY + r2.getLocalBounds().height;
		float playerRight = playerX + r1.getLocalBounds().width;
		float objRight = objX + r2.getLocalBounds().width;

		float bottomCollision = objBottom - playerY - 8;
		float topCollision = playerBottom - objY - 8;
		float leftCollision = playerRight - objX + 8;
		float rightCollision = objRight - playerX + 8;

		sf::Color debugColor;

		// Check if two objects are being touched on the BOTTOM
		if (bottomCollision <= topCollision 
			&& bottomCollision <= leftCollision 
			&& bottomCollision <= rightCollision)
		{
			overlap = CollisionDirection::bottom;
			debugColor = sf::Color::Blue;
		}

		// Check if two objects are being touched on the TOP
		if (topCollision <= bottomCollision 
			&& topCollision <= leftCollision 
			&& topCollision <= rightCollision)
		{
			overlap = CollisionDirection::top;
			debugColor = sf::Color::Yellow;
		}

		// Check if two objects are being touched on the RIGHT
		if (rightCollision <= leftCollision 
			&& rightCollision <= topCollision 
			&& rightCollision <= bottomCollision)
		{
			overlap = CollisionDirection::right;
			debugColor = sf::Color::Green;
		}

		// Check if two objects are being touched on the LEFT
		if (leftCollision <= rightCollision 
			&& leftCollision <= topCollision 
			&& leftCollision <= bottomCollision)
		{
			overlap = CollisionDirection::left;
			debugColor = sf::Color::Magenta;
		}

		if (debug)
		{
			sf::RectangleShape playerDebug;
			playerDebug.setSize(sf::Vector2f(32, 32));
			playerDebug.setPosition(playerX, playerY);
			playerDebug.setOutlineColor(debugColor);
			playerDebug.setOutlineThickness(3);

			sf::RectangleShape objectDebug;
			objectDebug.setSize(sf::Vector2f(32, 32));
			objectDebug.setPosition(objX, objY);
			objectDebug.setOutlineColor(debugColor);
			objectDebug.setOutlineThickness(3);

			this->window->draw(playerDebug);
			this->window->draw(objectDebug);
		}
	}

	return overlap;
}

Map::~Map()
{

}