#pragma once
#include <fstream>
#include "paceman.h"
#include "wall.h"
#include "blue_ghost.h"
#include "tile.h"
#include "candy.h"
#include "player.h"
#include "red_ghost.h"

class World {
public:
    World();
    void set_lives(int lives);
    void simulate_a_turn();
    void clear_world();
    void display_world(sf::RenderWindow& window);
    void display_score(sf::RenderWindow& window);
    void reset();
    void display_lives(sf::RenderWindow& window);
    int get_height();
    int get_width();
    vector<Tile*>& operator[](int index);
private:
    int score;
    bool cont;
    int lives;
    int height;
    int candy_count;
    Coord entrypoint;
    Coord player;
    Coord rghost;
    Coord bghost;
    int width;
    vector<vector<Tile*>> world;
};