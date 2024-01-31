#pragma once
#include "paceman.h"
#include "wall.h"
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
    void display_lives(sf::RenderWindow& window);
    vector<Tile*>& operator[](int index);
private:
    int score;
    bool cont;
    int lives;
    vector<vector<Tile*>> world;
};