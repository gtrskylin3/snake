#ifndef SNAKE_H
#define SNAKE_H


#define height 20
#define width 50
#define MAX_SNAKE 100
#include <stdbool.h>

typedef struct
{
    int x;
    int y;
} Point;

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Directions;


void move_snake(int snake_length, Point snake[], Directions dir);

bool collision_check(int snake_length, Point snake[]);

void init_snake(int snake_length, Point snake[]);

void spawn_food(Point *food, int snake_length, Point snake[]);

bool check_food(int snake_length, Point snake[], Point food);

#endif