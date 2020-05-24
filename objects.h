#ifndef OBJECTS_H
#define OBJECTS_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <list>
#include <ctime>
#include <cstdlib> // для функций rand() и srand()

#define GET_RECTANGLE(color, pos)              \
    sf::RectangleShape rectangle;              \
    rectangle.setSize(sf ::Vector2f(30, 30));  \
    rectangle.setFillColor(sf ::Color::color); \
    rectangle.setPosition(pos);                \


class Apple;

class Snake
{
public:
    enum Direction
    {
        UP = 1,
        LEFT,
        DOWN,
        RIGHT
    };

    Snake();

    void motion(sf::Event &event);
    std::vector<sf::Vector2i> snake_pos;
    short int current_Direction;
    void draw(sf::RenderWindow &window);
    void check_apple(Apple &apples);
    void check_wall(sf::RenderWindow &window);
    bool EATING;
    //Snake(const Snake&) = delete;
};

class Map
{
public:
    static const int map_size = 630;
    static const int size_block = 30;                                 //x (y)
    static const int HORIZANTAL_UPPER_BORDER = 0;                     //y
    static const int HORIZANTAL_LOWER_BORDER = map_size - size_block; //y
    static const int VERTICAL_LEFT_BORDER = 0;                        //x
    static const int VERTICAL_RIGHT_BORDER = map_size - size_block;   //x
    static const int NUMBER_BLOCKS = map_size / size_block;

    Map();

    sf::Vector2i blocks_pos[NUMBER_BLOCKS][NUMBER_BLOCKS];
    void draw(sf::RenderWindow &window);
    //Map(const Map &) = delete;
};

class Apple
{
public:
    std::vector<sf::Vector2i> apple_pos;
    void apple_create(const Snake &s);
    void draw(sf::RenderWindow &window);
    bool possible_Apple(const int a, const int b, const Snake &s);
};

#endif