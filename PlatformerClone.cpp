#include "Headers.h"
#include "Entity.h"
#include "Map.h"

// global variables

sf::Font font;

// debugging texts
sf::Text playerPosText;
sf::Text avgPhysicsTime;

sf::Vector2f viewPosition(0, 0);

Player player;

// where we do all the physics calculations, where everything is closley related to delta time
void physicsUpdate(float deltaTime, Map map, sf::RenderWindow *window)
{
    auto start = std::chrono::system_clock::now();

    map.updateBlocks(player);

    // this is sorting the map blocks vector based on their distance to the player
    // remove std::greater<Block*>() to make it sort based on smaller
    std::sort(map.map.begin(), map.map.end(), std::greater<Block*>());

    player.physicsUpdate(deltaTime, map, true);

    // testing player collisions with all the entities on the map
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

            // to save up on computations
            entity->draw(window);
        }
    }

    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed = end - start;

    // debug text update
    avgPhysicsTime.setString(sf::String(std::to_string(elapsed.count())));
}

// where we draw everything
void draw(sf::RenderWindow *window, sf::View *viewPort, Map map, float deltaTime)
{
    // moving the view port based on the player's position
    viewPosition.x = player.rect.getPosition().x - (window->getSize().x * 0.5f);
    viewPosition.y = player.rect.getPosition().y - (window->getSize().y * 0.5f);

    // moving the view based on the player's position
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
    window->draw(avgPhysicsTime);
}

int main()
{
    // loading the font for global usage
    font.loadFromFile("res\\sprites\\pix.ttf");

    // the actual window where we draw all the bullshit
    sf::RenderWindow window(sf::VideoMode(800, 800), "PlatfromerClone");
    window.setFramerateLimit(60);

    // initializing the player
    player = Player(150, 150, GAME_SCALE, GAME_SCALE, sf::Color(32, 38, 54), 200);

    // view port responsible for scrolling the view with the player
    // think of it as the camera
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

    avgPhysicsTime = sf::Text("", font, 48);
    avgPhysicsTime.setFillColor(sf::Color::Black);

    // basic framerate text for debugging
    sf::Text frameRate("", font, 48);
    frameRate.setFillColor(sf::Color::Black);

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

        avgPhysicsTime.setPosition(viewPosition.x + 200, viewPosition.y);

        window.setView(viewPort);

        window.clear(sf::Color(255, 255, 255));
        
        physicsUpdate(deltaTime, map, &window);

        draw(&window, &viewPort, map, deltaTime);
        window.draw(frameRate);
        window.display();
    }

    return 0;
}

// for testing purposes
int mainTest()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "PlatfromerClone");
    window.setFramerateLimit(60);

    player = Player(150, 150, GAME_SCALE, GAME_SCALE, sf::Color(32, 38, 54), 200);

    // the image we use to extrapolate map data
    sf::Image mapImage;
    mapImage.loadFromFile("res\\sprites\\map1.png");

    // intitializing the map with the map image
    Map map(mapImage, &window);
    map.render();

    sf::Clock clock;
    float deltaTime;

    // event handler for closing the game window
    sf::Event event;

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

        map.updateBlocks(player);

        window.clear(sf::Color(255, 255, 255));

        physicsUpdate(deltaTime, map, &window);

        window.draw(player.rect);

        for (Block* block : map.map)
        {
            window.draw(*block);

        }
        window.display();
    }

    return 0;
}