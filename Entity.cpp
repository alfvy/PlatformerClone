#include "Entity.h"
#include "Map.h"

Entity::Entity(){}
Player::Player(){}

Entity::Entity(int x, int y, int width, int height, sf::Color color, float speed) : 
    rect(sf::RectangleShape(sf::Vector2f(width, height))),
    speed(speed), alive(true), direction(true)
{
    this->rect.setPosition(x, y);
    this->rect.setFillColor(color);
}

Player::Player(int x, int y, int width, int height, sf::Color color, float speed)
{
    this->vel = sf::Vector2f(0, 0);
    this->speed = speed;
    this->direction = true;
    this->alive = true;

    this->rect = sf::RectangleShape();
    this->rect.setPosition(x, y);
    this->rect.setSize(sf::Vector2f(width, height));
    this->rect.setFillColor(color);
}

void Entity::draw(sf::RenderWindow* window)
{
    if (!alive) return;

	window->draw(this->rect);
}

void Player::draw(sf::RenderWindow* window)
{
    if (!alive) return;

    window->draw(this->rect);
}

void Entity::physicsUpdate(float deltaTime, Map map, bool debug)
{
    if (!alive) return;

    bool onGround = false;
    bool toLeft = false;
    bool toRight = false;
    bool toTop = false;

    // checking every block in the map
    for (sf::RectangleShape* block : map.map)
    {
        if (block->getFillColor() == sf::Color::Black)
        {
            /*onGround = playerColRect.intersects(block->getGlobalBounds());
            if (onGround) break;*/

            if (map.checkCollisionDirection(this->rect, *block, debug) == CollisionDirection::top)
            {
                onGround = true;
            }

            if (map.checkCollisionDirection(this->rect, *block, debug) == CollisionDirection::left)
            {
                toLeft = true;
            }

            if (map.checkCollisionDirection(this->rect, *block, debug) == CollisionDirection::right)
            {
                toRight = true;
            }

            if (map.checkCollisionDirection(this->rect, *block, debug) == CollisionDirection::bottom)
            {
                toTop = true;
            }

            if ((onGround && toLeft) || (onGround && toRight)) { break; }
        }
    }

    // if we hit our head buckle and stop all upwards momentum
    if (toTop)
    {
        this->rect.move(0, 1);
        this->vel.y = 0;
    }

    // if we're on the ground we stop "falling"
    if (onGround)
    {
        this->vel.y = 0;
    }
    else if (!onGround)// if we're in the air "fall"
    {
        this->vel.y += gravity * deltaTime;
    }

    if (onGround && direction)
    {
        this->vel.x = this->speed * deltaTime;
    }
    else if (onGround && !direction)
    {
        this->vel.x = -this->speed * deltaTime;

    }

    if (toLeft)
    {
        direction = false;
    }

    if (toRight)
    {
        direction = true;
    }

    // move the player based on the accumilated velocity
    // either through player controls or the "falling"
    this->rect.move(this->vel);
    this->vel.x = 0;
}

void Player::physicsUpdate(float deltaTime, Map map, bool debug)
{
    if (!alive) return;

    bool onGround = false;
    bool toLeft = false;
    bool toRight = false;
    bool toTop = false;
    bool overLapping = false;

    sf::RectangleShape topCollision;
    sf::RectangleShape bottomCollision;
    sf::RectangleShape leftCollision;
    sf::RectangleShape rightCollision;



    // checking every block in the map
    for (sf::RectangleShape* block : map.map)
    {
        if (block->getFillColor() == sf::Color::Black)
        {
            /*onGround = playerColRect.intersects(block->getGlobalBounds());
            if (onGround) break;*/

            if (map.checkCollisionDirection(this->rect, *block, debug) == CollisionDirection::top)
            {
                onGround = true;
                topCollision = *block;
            }

            if (map.checkCollisionDirection(this->rect, *block, debug) == CollisionDirection::left)
            {
                toLeft = true;
                leftCollision = *block;
            }

            if (map.checkCollisionDirection(this->rect, *block, debug) == CollisionDirection::right)
            {
                toRight = true;
                rightCollision = *block;
            }

            if (map.checkCollisionDirection(this->rect, *block, debug) == CollisionDirection::bottom)
            {
                toTop = true;
                bottomCollision = *block;
            }

            //if()

            if ((onGround && toLeft) || (onGround && toRight)) { break; }
        }
    }

    if (toTop)
    {
        this->rect.move(0, 1);
        this->vel.y = 0;
    }

    // if we're on the ground we stop "falling"
    if (onGround)
    {
        this->vel.y = 0;
        this->rect.setFillColor(sf::Color(90, 38, 54));
    }
    else if (!onGround)// if we're in the air "fall"
    {
        this->vel.y += gravity * deltaTime;
        this->rect.setFillColor(sf::Color(32, 38, 54));
    }

    // 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !toLeft)
    {
        this->vel.x = this->speed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !toRight)
    {
        this->vel.x = -this->speed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && onGround)
    {
        this->vel.y = -(this->speed * 1.5f) * deltaTime;
    }

    this->rect.move(this->vel);
    this->vel.x = 0;
}

Entity::~Entity(){}
Player::~Player(){}