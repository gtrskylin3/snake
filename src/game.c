#include "render.h"
#include "snake.h"


void draw_game_location(char game_map[height][width])
{
    for (int i = 0; i < height; ++i)
    {

        for (int j = 0; j < width; ++j)
        {
            char symbol = game_map[i][j];

            if (symbol == '#') {
                attron(COLOR_PAIR(1)); // Зеленый для стен
                mvaddch(i, j, symbol);
                attroff(COLOR_PAIR(1));
            } else if (symbol == '@') {
                attron(COLOR_PAIR(2)); // Синий для змейки
                mvaddch(i, j, symbol);
                attroff(COLOR_PAIR(2));
            } else if (symbol == '$') {
                attron(COLOR_PAIR(3)); // Красный для еды
                mvaddch(i, j, symbol);
                attroff(COLOR_PAIR(3));
            } else {
                mvaddch(i, j, ' ');
            }
        }
    }
}

void create_game_location(char game_map[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            game_map[i][j] = ' ';
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

void move_snake(int snake_length, Point snake[], Directions dir)
{
    for (int i = snake_length - 1; i > 0; i--)
    {
        snake[i] = snake[i-1];
    }
    switch (dir)
    {
        case UP: snake[0].y--; break;
        case DOWN: snake[0].y++; break;
        case LEFT: snake[0].x--; break;
        case RIGHT: snake[0].x++; break;
    }
}

bool collision_check(int snake_length, Point snake[]){
    if (snake[0].x <= 0 || snake[0].x >= width - 1 || 
        snake[0].y <= 0 || snake[0].y >= height - 1) {
        return true;
    }
    for (int i = 1; i < snake_length; i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            return true;
        }
    }
    return false;
}

void handle_input(Directions *dir) {
    int ch = getch();
    switch (ch)
    {
    case 'w': case 'W': case KEY_UP:
        if (*dir != DOWN) *dir = UP;
        break;
    case 's': case 'S': case KEY_DOWN:
        if (*dir != UP) *dir = DOWN;
        break;
    case 'a': case 'A': case KEY_LEFT:
        if (*dir != RIGHT) *dir = LEFT;
        break;
    case 'd': case 'D': case KEY_RIGHT:
        if (*dir != LEFT) *dir = RIGHT;
        break;
    }
}
void init_snake(int snake_length, Point snake[])
{
    snake[0].y = height / 2;
    snake[0].x = width / 2;
    for (int i = 1; i < snake_length; ++i)
    {
        snake[i].y = snake[i - 1].y;
        snake[i].x = snake[i - 1].x - 1;
    }
}

void draw_snake(char game_map[height][width], int snake_length, Point snake[])
{
    for (int i = 0; i < snake_length; ++i)
    {
        game_map[snake[i].y][snake[i].x] = '@';
    }
}

void draw_score(int snake_length){
    attron(COLOR_PAIR(4) | A_BOLD); // Желтый жирный текст
    mvprintw(0, 2, " SCORE: %d ", (snake_length - 3) * 10);
    attroff(COLOR_PAIR(4) | A_BOLD);
}

void draw_food(char game_map[height][width], Point food){
    game_map[food.y][food.x] = '$';
}
void render(Point food, int snake_length, Point snake[], char game_map[height][width])
{
    draw_snake(game_map, snake_length, snake);
    draw_food(game_map, food);
    clear();
    draw_game_location(game_map);
    draw_score(snake_length);
    refresh();
    usleep(100000);
}

void spawn_food(Point *food, int snake_length, Point snake[]){
    bool on_snake;
    do {
        on_snake = false;
        food->x = rand() % (width - 2) + 1;
        food->y = rand() % (height - 2) + 1;
        for (int i = 0; i < snake_length; ++i){
            if (snake[i].x == food->x && snake[i].y == food->y){
                on_snake = true;
                break;
            }
        }
    } while (on_snake);
}


bool check_food(int snake_length, Point snake[], Point food){
    return (snake[0].x == food.x && snake[0].y == food.y);
}