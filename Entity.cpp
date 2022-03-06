#include "Entity.h"
#include "Map.h"

Entity::Entity(){}
Player::Player(){}

// class initializer
Entity::Entity(int x, int y, int width, int height, sf::Color color, float speed) : 
    rect(sf::RectangleShape(sf::Vector2f(width, height))),
    speed(speed), alive(true), direction(true)
{
    this->rect.setPosition(x, y);
    this->rect.setFillColor(color);
}

// class initializer
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

void Entity::physicsUpdate(float deltaTime, Map *map, bool debug)
{
    // if the object is not alive stop all computations
    if (!alive) return;

    // booleans to check the objects collision direction
    bool onGround = false;
    bool toLeft = false;
    bool toRight = false;
    bool toTop = false;

    // checking every block in the map
    for (sf::RectangleShape* block : map->map)
    {
        // with the color black
        if (block->getFillColor() == sf::Color::Black)
        {
            /*onGround = playerColRect.intersects(block->getGlobalBounds());
            if (onGround) break;*/

            /*switch (map->checkCollisionDirection(this->rect, *block, debug))
            {
            case CollisionDirection::top:
                onGround = true;
                break;
            case CollisionDirection::left:
                toLeft = true;
                break;
            case CollisionDirection::right:
                toRight = true;
                break;
            case CollisionDirection::bottom:
                toTop = true;
                break;
            }*/

            //if (map->checkCollisionDirection(this->rect, *block, debug) == CollisionDirection::top)
            //{
            //    // if the entity is colliding with the top of another object
            //    onGround = true;
            //}

            if (map->checkCollisionDirection(this->rect, *block, debug) == CollisionDirection::left)
            {
                // if the entity is colliding with the right of another object
                toLeft = true;
            }

            if (map->checkCollisionDirection(this->rect, *block, debug) == CollisionDirection::right)
            {
                // if the entity is colliding with the right of another object
                toRight = true;
            }

            //if (map->checkCollisionDirection(this->rect, *block, debug) == CollisionDirection::bottom)
            //{
            //    // if the entity is colliding with the right of another object
            //    toTop = true;
            //}

            if ((onGround && toLeft) || (onGround && toRight)) { break; }
        }
    }

    // if we hit our head buckle and stop all upwards momentum
    //if (toTop)
    //{
    //    this->rect.move(0, 1);
    //    this->vel.y = 0;
    //}

    //// if we're on the ground we stop "falling"
    //if (onGround)
    //{
    //    this->vel.y = 0;
    //}
    //else if (!onGround)// if we're in the air "fall"
    //{
    //    this->vel.y += gravity * deltaTime;
    //}

    // if the entity is on the ground with direction right
    if (direction)
    {
        this->vel.x = this->speed * deltaTime;
    }
    else if (!direction) // if the entity is on the ground with direction left
    {
        this->vel.x = -this->speed * deltaTime;

    }

    // flipping the direction of the object only when colliding with the opposite direction
    if (toLeft)
    {
        direction = false;
    }
    if (toRight)
    {
        direction = true;
    }

    // move the entity based on the accumilated velocity
    // either through automated controls or the "falling"
    this->rect.move(this->vel);
    this->vel.x = 0;
}

void Player::physicsUpdate(float deltaTime, Map *map, bool debug)
{
    // if the object is not alive stop all computations
    if (!alive) return;

    // booleans to check the objects collision direction
    bool onGround = false;
    bool toLeft = false;
    bool toRight = false;
    bool toTop = false;
    // still haven't implemented the check for overlapping with other colliders
    bool overLapping = false;

    // the last object the player collided with pretaining to that direciton
    sf::RectangleShape topCollision;
    sf::RectangleShape bottomCollision;
    sf::RectangleShape leftCollision;
    sf::RectangleShape rightCollision;

    // checking every block in the map
    //for (sf::RectangleShape* block : map->map)
    for(int i = 0; i < 10; i++)
    {
        auto block = map->map[i];

        if (block->getFillColor() == sf::Color::Black)
        {
            /*onGround = playerColRect.intersects(block->getGlobalBounds());
            if (onGround) break;*/

            if (map->checkCollisionDirection(this->rect, *block, debug) == CollisionDirection::top)
            {
                // if the player is colliding with the top of another object
                onGround = true;
                topCollision = *block;
            }

            if (map->checkCollisionDirection(this->rect, *block, debug) == CollisionDirection::left)
            {
                // if the entity is colliding with the right of another object
                toLeft = true;
                leftCollision = *block;
            }

            if (map->checkCollisionDirection(this->rect, *block, debug) == CollisionDirection::right)
            {
                // if the entity is colliding with the left of another object
                toRight = true;
                rightCollision = *block;
            }

            if (map->checkCollisionDirection(this->rect, *block, debug) == CollisionDirection::bottom)
            {
                // if the entity is colliding with the bottom of another object
                toTop = true;
                bottomCollision = *block;
            }

            // if we're colliding with the ground and an object to the left or to the right stop the collision check
            if ((onGround && toLeft) || (onGround && toRight) || onGround) { break; }
        }
    }

    // shitty basics physics

    for (uint8_t i = 0; i < 4; i++)
    {
        int dist = util::distanceToCenter(this->rect.getGlobalBounds(), map->map[i]->getGlobalBounds());
        if (dist < this->rect.getGlobalBounds().height * 0.8f)
        {
            this->rect.move(0, -this->rect.getGlobalBounds().height * 0.2f);
            //std::cout << dist << " ";
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

    // basic player controls
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