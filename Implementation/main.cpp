#include "paceman.h"
#include "tile_world.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(720, 780), "Pace-Man");
    World w;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        w.simulate_a_turn();
        w.display_world(window);
        w.display_score(window);
        w.display_lives(window);
        window.display();
        sf::sleep(sf::milliseconds(150));
    }
    //Create a Board for the player
    return 0;
}
