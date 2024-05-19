#include "Menu.h"

using namespace std;

Menu::Menu(int h, int w) {
    if (!image.loadFromFile("./menu.png"))
    {
        cout << "Unable to load paceman.png";
        exit(1);
    }
    height = h;
    width = w;
    saidyes = 0;
}

void Menu::draw_menu(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("Retromic.ttf"))
    {
        cout << "Unable to load font\n";
        exit(1);
    }
    string title = "Pace-Man";
    sf::Text displaytitle;
    displaytitle.setCharacterSize(85);
    displaytitle.setPosition(width*2.0, height);
    displaytitle.setFont(font);
    displaytitle.setString(title);
    displaytitle.setFillColor(sf::Color(255, 219, 88));

    sf::Sprite spr;
    spr.setTexture(image);
    spr.setScale(0.5, 0.5);
    spr.setPosition(width * 2, height * 6);
    
    string mes = "Press Enter to continue...";
    sf::Text displaymes;
    displaymes.setPosition(width* 2, height * 20);
    displaymes.setFont(font);
    displaymes.setString(mes);
    displaymes.setFillColor(sf::Color::White);

    string rule = "Use Arrow Keys/WASD to move, watch out for some pesky ghosts!";
    sf::Text displayrule;
    displayrule.setPosition(width, height * 22);
    displayrule.setFont(font);
    displayrule.setString(rule);
    displayrule.setCharacterSize(14);
    displayrule.setFillColor(sf::Color::White);
    window.draw(displaytitle);
    window.draw(displayrule);
    window.draw(displaymes);
    window.draw(spr);
}

bool Menu::input_listener() {
    if (saidyes) {
        return true;
    }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
        saidyes = 1;
		return true;
	}
	return false;
}