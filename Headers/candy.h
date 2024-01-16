#pragma once
#include "paceman.h"
#include "tile.h"
class World;

class Candy : public Tile {
public:
    Candy(int x, int y, World& world) : Tile(x, y, world) {};
    void display(sf::RenderWindow& window);
    void move() {};
    void exit_house() {};
    bool check_exit() { return false; };
    Object_type who();
};
