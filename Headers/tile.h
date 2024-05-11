#pragma once
#include "paceman.h"
class World;

class Tile {
public:
    Tile(int x, int y, World& world);
    virtual void display(sf::RenderWindow& window) {};
    virtual Coord move() { return coord; };
    virtual Coord exit_house() { return coord; };
    virtual Object_type who();
    virtual Coord move(Coord player) { return coord; };
    virtual bool check_exit() { return false; };
    virtual int get_lives() { return 0; };
    virtual void set_lives(int life) { };

protected:
    Coord coord;
    World& world;
};