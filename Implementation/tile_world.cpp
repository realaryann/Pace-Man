#include "tile_world.h"

vector<Tile*>& World::operator[](int index)
{
    if (index >= height || index < 0)
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

int World::get_height() {
    return height;
}
int World::get_width() {
    return width;
}

void World::display_over(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("Retromic.ttf"))
    {
        cout << "Unable to load font\n";
        exit(1);
    }
    string ovr = "Game Over";
    sf::Text displayovr;
    displayovr.setCharacterSize(80);
    displayovr.setPosition(width * 2, height * 1);
    displayovr.setFont(font);
    displayovr.setString(ovr);
    displayovr.setFillColor(sf::Color::Red);

    sf::Sprite spr;
    spr.setTexture(endgame);
    spr.setScale(0.5, 0.5);
    spr.setPosition(width * 5, height * 8);

    string res = "Press 'R' to Restart";
    sf::Text displayres;
    displayres.setCharacterSize(30);
    displayres.setPosition(width * 4, height * 20);
    displayres.setFont(font);
    displayres.setString(res);
    displayres.setFillColor(sf::Color::Red);

    window.draw(spr);
    window.draw(displayres);
    window.draw(displayovr);
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
    displayscore.setPosition(width*12, height*22);
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
    displaylives.setPosition(width, height*22);
    displaylives.setString(live);
    displaylives.setFillColor(sf::Color::White);
    window.draw(displaylives);
}

void World::clear_world()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            delete world[i][j];
        }
    }
    ovr = 1;
}

void World::simulate_a_turn()
{
    //Reset Board
    int eaten = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (world[i][j]->who() == CANDY)
            {
                eaten++;
                delete world[i][j];
                world[i][j] = new Candy(j, i,*this);

            }
        }
    }
    //Count all candy on the board
    if (world[player.y][player.x]->get_lives() != lives)
    {
        //teleport player to origin, pause the game for 3 seconds.
        delete world[player.y][player.x];
        delete world[11][10];
        world[player.y][player.x] = new Tile(player.x, player.y, *this);
        world[11][10] = new Player(10, 11, *this);
        lives--;
        world[11][10]->set_lives(lives);
        player.x = 10;
        player.y = 11;
        return;
    }
    //Check for Lives 
    if (lives < 1)
    {
        //End Game
        clear_world();
        //set_game_over();

    }
    score = (candy_count-eaten)*20;
    //Player has moved
    player = world[player.y][player.x]->move();
    //Red_ghost has moved
    if (eaten < 157 && !(world[rghost.y][rghost.x]->check_exit()))
    {
        rghost=world[rghost.y][rghost.x]->exit_house(); //Red Ghost is now outside
    }
    if (world[rghost.y][rghost.x]->check_exit() == true)
    {
        rghost = world[rghost.y][rghost.x]->move();
    }
    if (eaten < 140 && !(world[bghost.y][bghost.x]->check_exit()))
    {
        bghost = world[bghost.y][bghost.x]->exit_house(); //blue Ghost is now outside
    }
    if (world[bghost.y][bghost.x]->check_exit())
    {
        bghost = world[bghost.y][bghost.x]->move(player);
    }
    if (eaten < 120 && !(world[oghost.y][oghost.x]->check_exit()))
    {
        oghost = world[oghost.y][oghost.x]->exit_house(); //orange Ghost is now outside
    }
    if (world[oghost.y][oghost.x]->check_exit()) {
        oghost = world[oghost.y][oghost.x]->move(player);
    }
}

void World::display_world(sf::RenderWindow& window)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            world[i][j]->display(window);
        }
    }
}

void World::reset() {
    cont = false;
    score = 0;
    ovr = 0;
    lives = 3;
    candy_count = 0;
    ifstream map;
    map.open("defaultmap.txt");
    map >> height;
    map >> width;
    world.resize(height);
    for (int i = 0; i < height; i++) {
        world[i].resize(width);
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            char c;
            map >> c;
            switch (c) {
            case 'x':
                world[i][j] = new Wall(j, i, *this);
                break;
            case 'o':
                candy_count++;
                world[i][j] = new Candy(j, i, *this);
                break;
            case 'b':
                world[i][j] = new Tile(j, i, *this);
                entrypoint.x = j;
                entrypoint.y = i;
                break;
            case '1':
                bghost.x = j;
                bghost.y = i;
                break;
            case '2':
                rghost.x = j;
                rghost.y = i;
                break;
            case '@':
                player.x = j;
                player.y = i;
                world[i][j] = new Player(j, i, *this);
                break;
            case 's':
                world[i][j] = new Tile(j, i, *this);
                break;
            }
        }
    }
    world[rghost.y][rghost.x] = new Red(rghost.x, bghost.y, entrypoint, *this);
    world[bghost.y][bghost.x] = new Blue(bghost.x, bghost.y, entrypoint, player, *this);
}

World::World()
{
    cont = false;
    score = 0;
    lives = 3;
    ovr = 0;
    candy_count = 0;
    if (!endgame.loadFromFile("./endgame.PNG")) {
        cout << "Unable to load Image endgame.PNG";
        exit(1);
    }
    ifstream map;
    map.open("defaultmap.txt");
    map >> height;
    map >> width;
    world.resize(height);
    for (int i = 0; i < height; i++) {
        world[i].resize(width);
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            char c;
            map >> c;
            switch (c) {
            case 'x':
                world[i][j] = new Wall(j, i, *this);
                break;
            case 'o':
                candy_count++;
                world[i][j] = new Candy(j, i, *this);
                break;
            case 'b':
                world[i][j] = new Tile(j, i, *this);
                entrypoint.x = j;
                entrypoint.y = i;
                break;
            case '1':
                bghost.x = j;
                bghost.y = i;
                break;
            case '2':
                rghost.x = j;
                rghost.y = i;
                break;
            case '3':
                oghost.x = j;
                oghost.y = i;
                break;
            case '@':
                player.x = j;
                player.y = i;
                world[i][j] = new Player(j, i, *this);
                break;
            case 's':
                world[i][j] = new Tile(j, i, *this);
                break;
            }
        }
    }
    world[rghost.y][rghost.x] = new Red(rghost.x, bghost.y, entrypoint, *this);
    world[bghost.y][bghost.x] = new Blue(bghost.x, bghost.y, entrypoint, player, *this);
    world[oghost.y][oghost.x] = new Orange(oghost.x, oghost.y, entrypoint, player, *this);
}