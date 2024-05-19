#include "paceman.h"
#include "tile_world.h"
#include "Menu.h"

int main()
{
    int x = 5;
    World w;
    sf::RenderWindow window(sf::VideoMode(w.get_width()*20.5, w.get_height()*25), "Pace-Man");
    Menu m(w.get_height(), w.get_width());
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::R) {
                    w.reset();
                }
            }
        }
        window.clear();
        if (!m.input_listener()) {
            m.draw_menu(window);
        }
        else {
            if (w.ovr == 1) {
                w.display_over(window);
            }
            else {
                w.simulate_a_turn();
                w.display_world(window);
                w.display_score(window);
                w.display_lives(window);
            }
        }
        window.display();
        sf::sleep(sf::milliseconds(150));
    }
    //Create a Board for the player
    return 0;
}
