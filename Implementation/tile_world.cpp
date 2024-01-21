#include "tile_world.h"

vector<Tile*>& World::operator[](int index)
{
    if (index >= BOARD_HEIGHT || index < 0)
    {
        cout << "Out of bounds access on world vector" << endl;
        exit(1);
    }
    return world[index];
}

void World::set_lives(int lives)
{
    if (lives >=0 && lives <=3)
    this->lives = lives;
}

void World::display_score(sf::RenderWindow& window)
{
    sf::Font font;
    if (!font.loadFromFile("Retromic.ttf"))
    {
        cout << "Unable to load font\n";
        exit(1);
    }
    string score = "Score: ";
    score = score + to_string(this->score);
    sf::Text displayscore;
    displayscore.setPosition(10.f, 725.f);
    displayscore.setFont(font);
    displayscore.setString(score);
    displayscore.setFillColor(sf::Color::White);
    window.draw(displayscore);
}

void World::display_lives(sf::RenderWindow& window)
{
    sf::Font font;
    if (!font.loadFromFile("Retromic.ttf"))
    {
        cout << "Unable to find font\n";
        exit(1);
    }
    string live="Lives: ";
    live = live + to_string(lives);
    sf::Text displaylives;
    displaylives.setFont(font);
    displaylives.setPosition(620.f, 725.f);
    displaylives.setString(live);
    displaylives.setFillColor(sf::Color::White);
    window.draw(displaylives);
}


void World::simulate_a_turn()
{
    //Reset Board
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            if (world[i][j]->who() == CANDY)
            {
                delete world[i][j];
                world[i][j] = new Candy(j, i,*this);
            }
        }
    }
    //Count all candy on the board
    int candy_count = 0, player_x,player_y,rghost_x,rghost_y;
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            if (world[i][j]->who() == CANDY)
            {
                candy_count++;
            }
            if (world[i][j]->who() == PLAYER)
            {
                player_x = i;
                player_y = j;
            }
            if (world[i][j]->who() == RED_GHOST)
            {
                rghost_x = i;
                rghost_y = j;
            }
        }
    }
    //cout << rghost_x<<" "<<rghost_y<<" "<<world[rghost_x][rghost_y]->who() << endl;
    if (world[player_x][player_y]->get_lives() != lives)
    {
        //teleport player to origin, pause the game for 3 seconds.
        delete world[player_x][player_y];
        delete world[19][17];
        world[player_x][player_y] = new Tile(player_y, player_x, *this);
        world[19][17] = new Player(17, 19, *this);
        lives--;
        world[19][17]->set_lives(lives);
        return;
    }
    score = 490-candy_count;
    //Player has moved
    world[player_x][player_y]->move();
    //Red_ghost has moved
    if (candy_count < 480 && !(world[rghost_x][rghost_y]->check_exit()))
    {
        world[rghost_x][rghost_y]->exit_house(); //Red Ghost is now outside
    }
    if (world[rghost_x][rghost_y]->check_exit() == true)
    {
        world[rghost_x][rghost_y]->move();
    }
}

void World::display_world(sf::RenderWindow& window)
{
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            world[i][j]->display(window);
        }
    }
}

World::World()
{
    score = 0;
    lives = 3;
    //Map Design
    //Initialize all possible blocks to be a "Tile"
    world.resize(BOARD_HEIGHT);
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        world[i].resize(BOARD_WIDTH);
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            world[i][j] = new Tile(j, i, *this);
        }
    }
    //Top Line
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        delete world[0][i];
        world[0][i] = new Wall(i, 0, *this);
    }
    //Top Left
    for (int i = 1; i < 10; i++)
    {
        delete world[i][0];
        world[i][0] = new Wall(0, i, *this);
    }
    for (int i = 1; i < 5; i++)
    {
        delete world[9][i];
        world[9][i] = new Wall(i, 9, *this);
    }
    for (int i = 10; i < 17; i++)
    {
        delete world[i][4];
        world[i][4] = new Wall(4, i, *this);
    }
    for (int i = 0; i < 4; i++)
    {
        delete world[16][i];
        world[16][i] = new Wall(i, 16, *this);
    }
    //top left rect
    for (int i = 2; i < 8; i++)
    {
        delete world[i][2];
        world[i][2] = new Wall(2, i, *this);
    }
    for (int i = 3; i < 8; i++)
    {
        delete world[2][i];
        world[2][i] = new Wall(i, 2, *this);
    }
    for (int i = 2; i < 8; i++)
    {
        delete world[i][8];
        world[i][8] = new Wall(8, i, *this);
    }
    for (int i = 2; i < 8; i++)
    {
        delete world[7][i];
        world[7][i] = new Wall(i, 7, *this);
    }
    //Top Right 
    for (int i = 1; i < 10; i++)
    {
        delete world[i][BOARD_WIDTH - 1];
        world[i][BOARD_WIDTH - 1] = new Wall(BOARD_WIDTH - 1, i, *this);
    }
    for (int i = BOARD_WIDTH - 1; i > 29; i--)
    {
        delete world[9][i];
        world[9][i] = new Wall(i, 9, *this);
    }
    for (int i = 10; i < 17; i++)
    {
        delete world[i][30];
        world[i][30] = new Wall(30, i, *this);
    }
    for (int i = BOARD_WIDTH - 1; i > 29; i--)
    {
        delete world[16][i];
        world[16][i] = new Wall(i, 16, *this);
    }
    //top right rect
    for (int i = BOARD_WIDTH - 3; i > 25; i--)
    {
        delete world[2][i];
        world[2][i] = new Wall(i, 2, *this);
    }
    for (int i = 2; i < 8; i++)
    {
        delete world[i][26];
        world[i][26] = new Wall(26, i, *this);
    }
    for (int i = 2; i < 8; i++)
    {
        delete world[i][32];
        world[i][32] = new Wall(32, i, *this);
    }
    for (int i = 26; i < 33; i++)
    {
        delete world[7][i];
        world[7][i] = new Wall(i, 7, *this);
    }
    //Bottom Line
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        delete world[BOARD_WIDTH - 1][i];
        world[BOARD_WIDTH - 1][i] = new Wall(i, BOARD_WIDTH - 1, *this);
    }
    //Bottom Left
    for (int i = BOARD_HEIGHT - 2; i > 24; i--)
    {
        delete world[i][0];
        world[i][0] = new Wall(0, i, *this);
    }
    for (int i = 1; i < 5; i++)
    {
        delete world[25][i];
        world[25][i] = new Wall(i, 25, *this);
    }
    for (int i = 25; i > 17; i--)
    {
        delete world[i][4];
        world[i][4] = new Wall(4, i, *this);
    }
    for (int i = 0; i < 5; i++)
    {
        delete world[18][i];
        world[18][i] = new Wall(i, 18, *this);
    }
    //Bottom left Rect
    for (int i = 27; i < 33; i++)
    {
        delete world[i][2];
        world[i][2] = new Wall(2, i, *this);
    }
    for (int i = 3; i < 9; i++)
    {
        delete world[27][i];
        world[27][i] = new Wall(i, 27, *this);
    }
    for (int i = 27; i < 33; i++)
    {
        delete world[i][8];
        world[i][8] = new Wall(8, i, *this);
    }
    for (int i = 2; i < 9; i++)
    {
        delete world[32][i];
        world[32][i] = new Wall(i, 32, *this);
    }
    for (int i = BOARD_WIDTH - 1; i > 29; i--)
    {
        delete world[18][i];
        world[18][i] = new Wall(i, 18, *this);
    }
    //Bottom Right
    for (int i = BOARD_HEIGHT - 2; i > 24; i--)
    {
        delete world[i][BOARD_WIDTH - 1];
        world[i][BOARD_WIDTH - 1] = new Wall(BOARD_WIDTH - 1, i, *this);
    }
    for (int i = BOARD_WIDTH - 1; i > 29; i--)
    {
        delete world[25][i];
        world[25][i] = new Wall(i, 25, *this);
    }
    for (int i = 25; i > 17; i--)
    {
        delete world[i][30];
        world[i][30] = new Wall(30, i, *this);
    }
    //Bottom right rec
    for (int i = 27; i < 33; i++)
    {
        delete world[i][26];
        world[i][26] = new Wall(26, i, *this);
    }
    for (int i = 26; i < 33; i++)
    {
        delete world[27][i];
        world[27][i] = new Wall(i, 27, *this);
    }
    for (int i = 27; i < 33; i++)
    {
        delete world[i][32];
        world[i][32] = new Wall(32, i, *this);
    }
    for (int i = 26; i < 33; i++)
    {
        delete world[32][i];
        world[32][i] = new Wall(i, 32, *this);
    }
    //ghost locker
    for (int i = 14; i < 21; i++)
    {
        delete world[10][i];
        world[10][i] = new Wall(i, 10, *this);
    }
    for (int i = 10; i < 16; i++)
    {
        delete world[i][14];
        world[i][14] = new Wall(14, i, *this);
    }
    for (int i = 10; i < 16; i++)
    {
        delete world[i][20];
        world[i][20] = new Wall(20, i, *this);
    }
    for (int i = 14; i < 21; i++)
    {
        delete world[15][i];
        world[15][i] = new Wall(i, 15, *this);
    }
    delete world[10][17];
    world[10][17] = new Tile(17, 10, *this);
    //lower cusp
    for (int i = 18; i < 26; i++)
    {
        delete world[i][6];
        world[i][6] = new Wall(6, i, *this);
    }
    for (int i = 6; i < 29; i++)
    {
        delete world[25][i];
        world[25][i] = new Wall(i, 25, *this);
    }
    for (int i = 18; i < 26; i++)
    {
        delete world[i][28];
        world[i][28] = new Wall(28, i, *this);
    }
    for (int i = 9; i < 17; i++)
    {
        delete world[i][6];
        world[i][6] = new Wall(6, i, *this);
    }
    for (int i = 6; i < 10; i++)
    {
        delete world[9][i];
        world[9][i] = new Wall(i, 9, *this);
    }
    for (int i = 9; i < 17; i++)
    {
        delete world[i][28];
        world[i][28] = new Wall(28, i, *this);
    }
    for (int i = 25; i < 29; i++)
    {
        delete world[9][i];
        world[9][i] = new Wall(i, 9, *this);
    }
    delete world[25][9];
    world[25][9] = new Tile(9, 25, *this);
    delete world[25][25];
    world[25][25] = new Tile(25, 25, *this);
    //Bottom Design with 2 block walls
    for (int i = 10; i < 25; i++)
    {
        delete world[27][i];
        world[27][i] = new Wall(i, 27, *this);
    }
    for (int i = 27; i < 33; i++)
    {
        delete world[i][10];
        world[i][10] = new Wall(10, i, *this);
    }
    for (int i = 12; i < 25; i++)
    {
        delete world[29][i];
        world[29][i] = new Wall(i, 29, *this);
    }
    for (int i = 29; i < 33; i++)
    {
        delete world[i][12];
        world[i][12] = new Wall(12, i, *this);
    }
    for (int i = 31; i < 33; i++)
    {
        delete world[i][14];
        world[i][14] = new Wall(14, i, *this);
    }
    for (int i = 31; i < 33; i++)
    {
        delete world[i][16];
        world[i][16] = new Wall(16, i, *this);
    }
    for (int i = 31; i < 33; i++)
    {
        delete world[i][18];
        world[i][18] = new Wall(18, i, *this);
    }
    for (int i = 31; i < 33; i++)
    {
        delete world[i][20];
        world[i][20] = new Wall(20, i, *this);
    }
    for (int i = 31; i < 33; i++)
    {
        delete world[i][22];
        world[i][22] = new Wall(22, i, *this);
    }
    for (int i = 31; i < 33; i++)
    {
        delete world[i][24];
        world[i][24] = new Wall(24, i, *this);
    }
    for (int i = 10; i < 17; i++)
    {
        delete world[i][11];
        world[i][11] = new Wall(11, i, *this);
    }
    for (int i = 10; i < 17; i++)
    {
        delete world[i][12];
        world[i][12] = new Wall(12, i, *this);
    }
    for (int i = 11; i < 17; i++)
    {
        delete world[i][9];
        world[i][9] = new Wall(9, i, *this);
    }
    for (int i = 11; i < 17; i++)
    {
        delete world[i][8];
        world[i][8] = new Wall(8, i, *this);
    }
    delete world[12][12];
    world[12][12] = new Tile(12, 12, *this);
    delete world[12][11];
    world[12][11] = new Tile(11, 12, *this);
    delete world[14][8];
    world[14][8] = new Tile(8, 14, *this);
    delete world[14][9];
    world[14][9] = new Tile(9, 14, *this);
    for (int i = 10; i < 17; i++)
    {
        delete world[i][22];
        world[i][22] = new Wall(22, i, *this);
    }
    for (int i = 10; i < 17; i++)
    {
        delete world[i][23];
        world[i][23] = new Wall(23, i, *this);
    }
    delete world[12][22];
    world[12][22] = new Tile(22, 12, *this);
    delete world[12][23];
    world[12][23] = new Tile(23, 12, *this);
    for (int i = 11; i < 17; i++)
    {
        delete world[i][25];
        world[i][25] = new Wall(25, i, *this);
    }
    for (int i = 11; i < 17; i++)
    {
        delete world[i][26];
        world[i][26] = new Wall(26, i, *this);
    }
    delete world[14][25];
    delete world[14][26];
    world[14][25] = new Tile(25, 14, *this);
    world[14][26] = new Tile(26, 14, *this);
    //Lower straight lines below ghost cell
    for (int i = 8; i < 27; i++)
    {
        delete world[18][i];
        world[18][i] = new Wall(i, 18, *this);
    }
    for (int i = 8; i < 27; i++)
    {
        delete world[20][i];
        world[20][i] = new Wall(i, 20, *this);
    }
    for (int i = 14; i < 21; i++)
    {
        delete world[17][i];
        world[17][i] = new Wall(i, 17, *this);
    }
    for (int i = 22; i < 24; i++)
    {
        delete world[i][8];
        world[i][8] = new Wall(8, i, *this);
    }
    for (int i = 10; i < 14; i++)
    {
        delete world[22][i];
        world[22][i] = new Wall(i, 22, *this);
    }
    for (int i = 21; i < 25; i++)
    {
        delete world[22][i];
        world[22][i] = new Wall(i, 22, *this);
    }
    for (int i = 22; i < 24; i++)
    {
        delete world[i][26];
        world[i][26] = new Wall(26, i, *this);
    }
    delete world[23][22];
    world[23][22] = new Wall(22, 23, *this);
    delete world[23][23];
    world[23][23] = new Wall(23, 23, *this);
    delete world[23][11];
    world[23][11] = new Wall(11, 23, *this);
    delete world[23][12];
    world[23][12] = new Wall(12, 23, *this);
    for (int i = 15; i < 20; i++)
    {
        delete world[22][i];
        world[22][i] = new Wall(i, 22, *this);

    }
    for (int i = 17; i < 18; i++)
    {
        delete world[23][i];
        world[23][i] = new Wall(i, 23, *this);
    }
    for (int i = 10; i < 17; i++)
    {
        delete world[7][i];
        world[7][i] = new Wall(i, 7, *this);
    }
    for (int i = 18; i < 25; i++)
    {
        delete world[7][i];
        world[7][i] = new Wall(i, 7, *this);
    }
    delete world[8][13];
    world[8][13] = new Wall(13, 8, *this);
    delete world[8][21];
    world[8][21] = new Wall(21, 8, *this);
    for (int i = 10; i < 15; i++)
    {
        delete world[4][i];
        world[4][i] = new Wall(i, 4, *this);
    }
    for (int i = 16; i < 19; i++)
    {
        delete world[4][i];
        world[4][i] = new Wall(i, 4, *this);
    }
    for (int i = 20; i < 25; i++)
    {
        delete world[4][i];
        world[4][i] = new Wall(i, 4, *this);
    }
    for (int i = 10; i < 15; i++)
    {
        delete world[2][i];
        world[2][i] = new Wall(i, 2, *this);
    }
    for (int i = 16; i < 19; i++)
    {
        delete world[2][i];
        world[2][i] = new Wall(i, 2, *this);
    }
    for (int i = 20; i < 25; i++)
    {
        delete world[2][i];
        world[2][i] = new Wall(i, 2, *this);
    }
    delete world[5][24];
    world[5][24] = new Wall(24, 5, *this);
    delete world[5][10];
    world[5][10] = new Wall(10, 5, *this);
    delete world[5][17];
    world[5][17] = new Wall(17, 5, *this);
    //Turn all empty tiles into Candy
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            if (world[i][j]->who() == TILE)
            {
                world[i][j] = new Candy(j, i, *this);
            }
        }
    }
    //Turn non Candy zones into tiles again
    //Left zones
    for (int i = 10; i < 16; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            delete world[i][j];
            world[i][j] = new Tile(j, i, *this);
        }
    }
    for (int i = 19; i < 25; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            delete world[i][j];
            world[i][j] = new Tile(j, i, *this);
        }
    }
    //Right Zones
    for (int i = 10; i < 16; i++)
    {
        for (int j = 31; j < BOARD_WIDTH; j++)
        {
            delete world[i][j];
            world[i][j] = new Tile(j, i, *this);

        }
    }
    for (int i = 19; i < 25; i++)
    {
        for (int j = 31; j < BOARD_WIDTH; j++)
        {
            delete world[i][j];
            world[i][j] = new Tile(j, i, *this);

        }
    }
    //Ghost Spawn candy removal
    for (int i = 11; i < 15; i++)
    {
        for (int j = 15; j < 20; j++)
        {
            delete world[i][j];
            world[i][j] = new Tile(j, i, *this);
        }
    }
    delete world[10][17];
    world[10][17] = new Tile(17, 10, *this);
    //Upper left Box removal
    for (int i = 3; i < 7; i++)
    {
        for (int j = 3; j < 8; j++)
        {
            delete world[i][j];
            world[i][j] = new Tile(j, i, *this);
        }
    }
    //Upper right box removal
    for (int i = 3; i < 7; i++)
    {
        for (int j = 27; j < 32; j++)
        {
            delete world[i][j];
            world[i][j] = new Tile(j, i, *this);
        }
    }
    //Lower right box removal
    for (int i = 28; i < 32; i++)
    {
        for (int j = 27; j < 32; j++)
        {
            delete world[i][j];
            world[i][j] = new Tile(j, i, *this);
        }
    }
    //Lower left Box removal
    for (int i = 28; i < 32; i++)
    {
        for (int j = 3; j < 8; j++)
        {
            delete world[i][j];
            world[i][j] = new Tile(j, i, *this);
        }
    }
    //Spawn Point
    delete world[19][17];
    world[19][17] = new Player(17, 19, *this);
    //Red Ghost Spawn
    delete world[12][16];
    world[12][16] = new Red(16, 12, *this);
    //Delete Ghost exit coin
    delete world[9][17];
    world[9][17] = new Tile(17, 9, *this);
}