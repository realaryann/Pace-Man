#pragma once
#include "paceman.h"
class World;

class Tile {
public:
    Tile(int x, int y, World& world);
    virtual void display(sf::RenderWindow& window) {};
    virtual void move() {};
    virtual void exit_house() {};
    virtual Object_type who();
    virtual bool check_exit() { return false; };

protected:
    Coord coord;
    World& world;
};