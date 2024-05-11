#pragma once
#include "paceman.h"
#include "tile.h"

class World;

class Wall :public Tile {
public:
    Wall(int x, int y, World& world) :Tile(x, y, world) {};
    void display(sf::RenderWindow& window);
    Coord move() { return coord; };
    Coord exit_house() { return coord; };
    bool check_exit() { return false; };
    int get_lives() { return 0; }
    void set_lives(int life) {};
    Object_type who();
};
