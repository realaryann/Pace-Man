#pragma once
#include <iostream>
#include <ctime>
#include <string>
#include <SFML/Graphics.hpp>
#include <string>
#include <cstdlib>
#include <vector>
#include <utility>
using namespace std;

const int BOARD_HEIGHT = 35;
const int BOARD_WIDTH = 35;

enum Object_type { TILE, PLAYER, CANDY, RED_GHOST, BLUE_GHOST, GREEN_GHOST, WALL };

enum Direction { LEFT, UP, DOWN, RIGHT, STAY };

struct Coord {
    int x;
    int y;
};

