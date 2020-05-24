#include "objects.h"


void Apple::apple_create(const Snake &s)
{
    int a, b;
    do
    {
        a = (rand() % (Map::NUMBER_BLOCKS - 2)) + 1;
        b = (rand() % (Map::NUMBER_BLOCKS - 2)) + 1;
    } while (!(possible_Apple(a, b, s)));

    this->apple_pos.push_back({a * 30, b * 30});
}

bool Apple::possible_Apple(const int a, const int b, const Snake &s)
{
    for (int i = 0; i < s.snake_pos.size(); ++i)
    {
        if ((a * 30 == s.snake_pos[i].x) && (b * 30 == s.snake_pos[i].y))
        {
            return false;
        }
    }
    for (int i = 0; i < apple_pos.size(); ++i)
    {
        if ((a * 30 == apple_pos[i].x) && (b * 30 == apple_pos[i].y))
        {

            return false;
        }
    }
    return true;
}

void Snake::check_apple(Apple &apples)
{
    EATING = false;
    for (int i = 0; i < apples.apple_pos.size(); ++i)
    {
        if (apples.apple_pos[i] == snake_pos[0])
        {
            apples.apple_pos.erase(apples.apple_pos.begin() + i);
            EATING = true;
        }
    }
}

void Snake::check_wall(sf::RenderWindow &window)
{
    if ((snake_pos[0].x == 0) || (snake_pos[0].y == 0) || (snake_pos[0].x == Map::map_size - Map::size_block) || (snake_pos[0].y == Map::map_size - Map::size_block))
    {
        window.close();
        printf("YOUR SCORE: %ld BYE!", snake_pos.size());
        exit(0);
    }
    for (int i = 2; i < snake_pos.size(); ++i)
    {
        if ((snake_pos[0] == snake_pos[i]))
        {
            window.close();
            printf("YOUR SCORE: %ld BYE!", snake_pos.size());
            exit(0);
        }
    }
}

void Apple::draw(sf::RenderWindow &window)
{
    for (int i = 0; i < apple_pos.size(); ++i)
    {
        GET_RECTANGLE(Red, (sf::Vector2f)apple_pos[i])
        window.draw(rectangle);
    }
}

Snake::Snake() : current_Direction(UP),
                 EATING(false)
{
    snake_pos = {{300, 300}};
}

Map::Map()
{
    for (int i = 0; i < NUMBER_BLOCKS; ++i)
    {
        for (int j = 0; j < NUMBER_BLOCKS; ++j)
        {
            blocks_pos[i][j] = {i * 30, j * 30};
        }
    }
}

void Snake::draw(sf::RenderWindow &window)
{
    switch (current_Direction)
    {
    case UP:
        snake_pos[0].y -= Map::size_block;
        break;
    case DOWN:
        snake_pos[0].y += Map::size_block;
        break;
    case LEFT:
        snake_pos[0].x -= Map::size_block;
        break;
    case RIGHT:
        snake_pos[0].x += Map::size_block;
        break;
    default:
        snake_pos[0].y -= Map::size_block;
        break;
    }

    if (EATING)
    {
        auto supp = snake_pos.back();
        for (int i = snake_pos.size(); i > 0; i--) //??
        {
            snake_pos[i] = snake_pos[i - 1];
        }
        snake_pos.push_back(supp);
    }
    else
    {
        for (int i = snake_pos.size(); i > 0; i--) //??
        {
            snake_pos[i] = snake_pos[i - 1];
        }
    }

    for (int i = snake_pos.size(); i > 0; i--) //??
    {
        GET_RECTANGLE(Green, (sf::Vector2f)snake_pos[i])
        window.draw(rectangle);
    }
}

void Map::draw(sf::RenderWindow &window)
{
    for (int i = 0; i < Map::NUMBER_BLOCKS; ++i)
    {
        for (int j = 0; j < Map::NUMBER_BLOCKS; ++j)
        {
            if ((i == Map::NUMBER_BLOCKS - 1) || (j == Map::NUMBER_BLOCKS - 1) || (i == 0) || (j == 0))
            {
                GET_RECTANGLE(Magenta, (sf::Vector2f)blocks_pos[i][j])
                window.draw(rectangle);
            }
            else
            {
                GET_RECTANGLE(Black, (sf::Vector2f)blocks_pos[i][j])
                rectangle.setOutlineThickness(2.f);
                rectangle.setOutlineColor(sf::Color::White);
                window.draw(rectangle);
            }
        }
    }
}

void Snake::motion(sf::Event &event)
{
    if (event.type == sf::Event::KeyReleased && snake_pos.size() == 1)
    {
        if (event.key.code == sf::Keyboard::Up)
        {
            current_Direction = Snake::UP;
        }
        else if (event.key.code == sf::Keyboard::Down)
        {
            current_Direction = Snake::DOWN;
        }
        else if (event.key.code == sf::Keyboard::Left)
        {
            current_Direction = Snake::LEFT;
        }
        else if (event.key.code == sf::Keyboard::Right)
        {
            current_Direction = Snake::RIGHT;
        }
    }
    else if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::Up)
        {
            if (snake_pos[2].x == snake_pos[0].x)
                return;
            current_Direction = Snake::UP;
        }
        else if (event.key.code == sf::Keyboard::Down)
        {
            if (snake_pos[2].x == snake_pos[0].x)
                return;
            current_Direction = Snake::DOWN;
        }
        else if (event.key.code == sf::Keyboard::Left)
        {
            if (snake_pos[2].y == snake_pos[0].y)
                return;
            current_Direction = Snake::LEFT;
        }
        else if (event.key.code == sf::Keyboard::Right)
        {
            if (snake_pos[2].y == snake_pos[0].y)
                return;
            current_Direction = Snake::RIGHT;
        }
    }
}