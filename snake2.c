#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>
#define height 20
#define width 40

void draw_game_location(char game_map[height][width])
{
    for (int i = 0; i < height; ++i)
    {

        for (int j = 0; j < width; ++j)
        {
            printf("%c", game_map[i][j]);
        }
        printf("\n");
    }
}

void create_game_location(char game_map[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            game_map[i][j] = '.';
        }
    }

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if ((i == 0 || i == height - 1) || (j == 0 || j == width - 1))
            {
                game_map[i][j] = '#';
            }
        }
    }
}

typedef struct
{
    int x;
    int y;
} Point;

void move_snake(int snake_length, Point snake[snake_length])
{
    for (int i = snake_length - 1; i > 0; i--)
    {
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
    }
    snake[0].x++;
    if (snake[0].x > width - 2)
    {
        snake[0].x = 1;
    }
}

void init_snake(int snake_length, Point snake[snake_length])
{
    snake[0].y = rand() % (height - 2) + 1;
    snake[0].x = rand() % (width - 2) + 1;
    for (int i = 1; i < snake_length; ++i)
    {
        snake[i].y = snake[i - 1].y;
        snake[i].x = snake[i - 1].x - 1;
    }
}

void draw_snake(char game_map[height][width], int snake_length, Point snake[snake_length])
{
    for (int i = 0; i < snake_length; ++i)
    {
        game_map[snake[i].y][snake[i].x] = 'o';
    }
}

void cursor_fix()
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(console, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(console, &cursorInfo);
}

void clear_screen()
{
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}
void render(char game_map[height][width])
{
    clear_screen();
    draw_game_location(game_map);
    Sleep(80);
}

int main()
{
    cursor_fix();
    int snake_length = 3;
    srand(time(NULL));
    char game_map[height][width];
    Point snake[snake_length];
    init_snake(snake_length, snake);
    system("cls");
    while (true)
    {
        create_game_location(game_map);
        move_snake(snake_length, snake);
        draw_snake(game_map, snake_length, snake);
        render(game_map);
    }
}