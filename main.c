#include "render.h"
#include "snake.h"

int main()
{
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(0);
    if (has_colors()){
        start_color();
        use_default_colors();
        init_pair(1, COLOR_WHITE, -1);
        init_pair(2, COLOR_GREEN, -1);
        init_pair(3, COLOR_RED, -1);
        init_pair(4, COLOR_YELLOW, -1);
    }
    srand(time(NULL));
    int snake_length = 3;
    char game_map[height][width];
    Point snake[MAX_SNAKE];
    Point food;
    Directions dir = RIGHT;
    init_snake(snake_length, snake);
    system("clear");
    spawn_food(&food, snake_length, snake);
    while (true)
    {
        create_game_location(game_map);
        handle_input(&dir);
        move_snake(snake_length, snake, dir);
        if (collision_check(snake_length, snake)){
            break;
        }
        if (check_food(snake_length, snake, food)){
            if (snake_length < MAX_SNAKE){
                snake[snake_length] = snake[snake_length - 1];
                snake_length++;
            }
            spawn_food(&food, snake_length, snake);
        }
        render(food, snake_length, snake, game_map);
    }
    endwin();
    printf("Game Over! Вы пососали!\n");
    return 0;
}