#pragma once
#include "paceman.h"
#include "tile.h"

class World;

class Wall :public Tile {
public:
    Wall(int x, int y, World& world) :Tile(x, y, world) {};
    void display(sf::RenderWindow& window);
    void move() {};
    void exit_house() {};
    bool check_exit() { return false; };
    Object_type who();
};
