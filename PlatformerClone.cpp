#include "Headers.h"
#include "Entity.h"
#include "Map.h"

// global variables

sf::Font font;

sf::Text playerPosText;

//sf::RectangleShape player;

sf::Vector2f viewPosition(0, 0);
sf::Vector2f playerVelocity(0, 0);

Entity testEnemy;

Player player;



// where we do all the physics calculations, where everything is closley related to delta time
void physicsUpdate(float deltaTime, Map map, sf::RenderWindow *window)
{
    player.physicsUpdate(deltaTime, map, true);

    for (Entity* entity : *map.entities)
    {
        if (entity->alive)
        {
            entity->physicsUpdate(deltaTime, map, true);

            if (player.rect.getGlobalBounds().intersects(entity->rect.getGlobalBounds()))
            {
                entity->rect.setFillColor(sf::Color::Cyan);
            }
            else { entity->rect.setFillColor(sf::Color::Red); }

            if (map.checkCollisionDirection(player.rect, entity->rect) == CollisionDirection::top)
            {
                entity->alive = false;
            }

            entity->draw(window);
        }
    }
}

// where we draw everything
void draw(sf::RenderWindow *window, sf::View *viewPort, Map map, float deltaTime)
{
    // moving the view port based on the player's position
    viewPosition.x = player.rect.getPosition().x - (window->getSize().x * 0.5f);
    viewPosition.y = player.rect.getPosition().y - (window->getSize().y * 0.5f);

    viewPort->reset(sf::FloatRect(viewPosition.x, viewPosition.y, 700, 700));

    // drawing every block on the map
    for (sf::RectangleShape* block : map.map)
    {
        window->draw(*block);
    }

    // misc debug
    {
        std::string playerPosString = std::to_string(int(player.rect.getPosition().x)) +
            "\n" + std::to_string(int(player.rect.getPosition().y));
        playerPosText.setFillColor(sf::Color::White);
        playerPosText.setPosition(player.rect.getPosition());
        playerPosText.setString(sf::String(playerPosString));
    }

    player.draw(window);
    
    window->draw(playerPosText);
}

int main()
{
    font.loadFromFile("res\\sprites\\pix.ttf");

    sf::RenderWindow window(sf::VideoMode(800, 800), "PlatfromerClone");
    window.setFramerateLimit(60);

    player = Player(150, 150, GAME_SCALE, GAME_SCALE, sf::Color(32, 38, 54), 200);

    // view port responsible for scrolling the view with the player
    sf::View viewPort;
    viewPort.reset(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));

    // clock for physics calucations
    sf::Clock clock;
    float deltaTime;

    // event handler for closing the game window
    sf::Event event;

    // the image we use to extrapolate map data
    sf::Image mapImage;
    mapImage.loadFromFile("res\\sprites\\map1.png");

    // intitializing the map with the map image
    Map map(mapImage, &window);
    map.render();

    // for debugging purposes
    playerPosText = sf::Text("", font, 15);

    // basic framerate text for debugging
    sf::Text frameRate("", font, 48);
    frameRate.setFillColor(sf::Color::Black);

    testEnemy = Entity(400, 150, GAME_SCALE, GAME_SCALE, sf::Color::Red, 120);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        deltaTime = clock.getElapsedTime().asSeconds();
        clock.restart();

        frameRate.setString(std::to_string(int(1 / deltaTime)));
        frameRate.setPosition(viewPosition);

        window.setView(viewPort);

        window.clear(sf::Color(255, 255, 255));
        
        physicsUpdate(deltaTime, map, &window);

        draw(&window, &viewPort, map, deltaTime);
        window.draw(frameRate);
        window.display();
    }

    return 0;
}

float distanceToCenter(sf::FloatRect obj1, sf::FloatRect obj2)
{
    sf::Vector2f obj1Center(obj1.left - (obj1.width * 0.5f), obj1.top - (obj1.width * 0.5f));
    sf::Vector2f obj2Center(obj2.left - (obj2.width * 0.5f), obj2.top - (obj2.width * 0.5f));

    return std::sqrt(
        ((obj1Center.x - obj1Center.x) * (obj1Center.x - obj1Center.x))
        + ((obj1Center.y - obj1Center.y) * (obj1Center.y - obj1Center.y))
    );
}

float diagonalLength(sf::FloatRect rect)
{
    return std::sqrt(((rect.width) * (rect.width)) + ((rect.height) * (rect.height)));
}