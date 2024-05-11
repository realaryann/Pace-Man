#pragma once
#include "paceman.h"
#include "tile.h"
#include "wall.h"
#include "tile_world.h"

class Blue : public Tile {
public:
	Blue(int x, int y, Coord entryp, Coord player, World& world) : Tile(x, y, world) {
		gate = entryp;
		playerloc = player;
		dir = STAY;
		exithouse = false;
		if (!texture.loadFromFile("./blueghost.png")) {
			cout << "Unable to find blueghost.png";
			exit(1);
		}
	};
	bool check_exit()
	{
		return exithouse;
	}
	Coord move(Coord player);
	Coord exit_house();
	Object_type who();
	void display(sf::RenderWindow& window);
private:
	sf::Texture texture;
	Direction dir;
	Coord playerloc;
	Coord gate;
	bool exithouse;
	bool onacandy;
};
