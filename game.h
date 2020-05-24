#ifndef GAME_H
#define GAME_H

#include "objects.h"

class Game
{
public:
    Snake main_snake;
    Map map;
    Apple apples;

    sf::RenderWindow window;

    sf::Clock clock_game;
    sf::Clock clock_game_frame;
    sf::Clock clock_apples;

    float time_game;

    Game();

    void run();
};

#endif