#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Menu {

public:
	Menu(int h, int w);
	void draw_menu(sf::RenderWindow& window);
	bool input_listener();
private:
	sf::Texture image;
	int saidyes;
	int height;
	int width;
};