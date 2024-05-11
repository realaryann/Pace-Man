#pragma once
#include "paceman.h"
#include "tile.h"
#include "wall.h"
#include "tile_world.h"

class World;

class Red : public Tile {
public:
    Red(int x, int y, Coord entry, World& world) : Tile(x, y, world) {
        gate = entry;
        dir = STAY;
        exithouse = false;
        if (!texture.loadFromFile("./redghost.png")){

            cout << "Unable to load redghost.png";
            exit(1);
        }
    };
    Object_type who();
    Coord exit_house();
    Coord move();
    void display(sf::RenderWindow& window);
    int get_lives() { return 0; }
    void set_lives(int life) {};
    bool check_exit()
    {
        return exithouse;
    }
private:
    sf::Texture texture;
    Coord gate;
    bool onacandy;
    bool exithouse;
    Direction dir;
};