#pragma once
#include "paceman.h"
#include "tile.h"
#include "tile_world.h"

class Player : public Tile {
public:
    Player(int x, int y, World& world) : Tile(x, y, world) { dir = STAY; lives = 3; };
    Object_type who();
    void move();
    void exit_house() {};
    bool check_exit() { return false; };
    void display(sf::RenderWindow& window);
    int get_lives() { return lives; };
    void set_lives(int life);
private:
    Direction dir;
    int lives;
};

