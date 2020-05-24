#include "game.h"

Game::Game() : main_snake(Snake()),
               map(Map()),
               apples(Apple()),
               window(sf::VideoMode(Map::map_size, Map::map_size), "Snake"),
               time_game(0.0),
               clock_game(sf::Clock())
{}



void Game::run()
{
    std::cout << "Введите уровень сложности (сложность ~ числу) 1, 2, 3?\n";
    std::string s;
    std::getline(std::cin, s);

    if (s == "1")
    {
        time_game = 1.0;
    }
    else if (s == "2")
    {
        time_game = 0.5;
    }
    else if (s == "3")
    {
        time_game = 0.2;
    }
    else
    {
        std::cout << "Попытайтесь снова!\n";
        exit(0);
    }

    std::cout << "Частота отрисовки -30, 60, 150?\n";
    std::getline(std::cin, s);

    if (s == "1")
    {
        window.setFramerateLimit(30);
    }
    else if (s == "2")
    {
        window.setFramerateLimit(60);
    }
    else if (s == "3")
    {
        window.setFramerateLimit(150);
    }
    else
    {
        std::cout << "Попытайтесь снова!\n";
    }

    std::cout << "Приятной игры!\n";

    srand((time(0)));
    apples.apple_create(main_snake);



    while (window.isOpen())
    {
        float Framerate = 1.f / clock_game_frame.getElapsedTime().asSeconds();
        clock_game_frame.restart();
        std::cout << "\r IPS: " << Framerate;

        sf::Event event;
        while (window.pollEvent(event))
        {

            main_snake.motion(event);

            if (event.type == sf::Event::Closed)
            {
                exit(0);
            }
        }

        main_snake.check_wall(window);

        if (clock_apples.getElapsedTime().asSeconds() > 1.0)
        {
            apples.apple_create(main_snake);
            clock_apples.restart();
        }

        if (clock_game.getElapsedTime().asSeconds() > time_game)
        {
            clock_game.restart();
            main_snake.check_apple(apples);
            map.draw(window);
            apples.draw(window);
            main_snake.draw(window);
            window.display();
        }

        window.clear();
    }
}