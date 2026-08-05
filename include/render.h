#ifndef RENDER_H
#define RENDER_H


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>
#include "snake.h"



void draw_game_location(char game_map[height][width]);

void create_game_location(char game_map[height][width]);

void handle_input(Directions *dir);

void draw_snake(char game_map[height][width], int snake_length, Point snake[]);

void draw_score(int snake_length);

void draw_food(char game_map[height][width], Point food);

void render(Point food, int snake_length, Point snake[], char game_map[height][width]);
#endif