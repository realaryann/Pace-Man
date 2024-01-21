#pragma once
#include "paceman.h"
#include "tile.h"
#include "wall.h"
#include "tile_world.h"


class World;

class Red :public Tile {
public:
    Red(int x, int y, World& world) : Tile(x, y, world) { exithouse = false; };
    Object_type who();
    void exit_house();
    void move();
    void display(sf::RenderWindow& window);
    int get_lives() { return 0; }
    void set_lives(int life) {};
    bool check_exit()
    {
        return exithouse;
    }
private:
    bool onacandy;
    bool exithouse;
};