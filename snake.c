#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>

#define height 20
#define width 40

// Структура точки
typedef struct {
    int x;
    int y;
} Point;

// Очистка экрана без мерцания (перенос курсора в начало)
void clear_screen() {
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

// Проверяем, находится ли змейка в этих координатах
bool is_snake_here(int x, int y, int snake_length, Point* snake) {
    for (int i = 0; i < snake_length; ++i) {
        if (snake[i].x == x && snake[i].y == y) {
            return true;
        }
    }
    return false;
}

// Отрисовка карты прямо на лету
void draw_game(int snake_length, Point* snake) {
    clear_screen();
    
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            // Если это змейка — выводим эмодзи
            if (is_snake_here(j, i, snake_length, snake)) {
                printf("🟢"); 
            }
            // Если это границы
            else if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                printf("🧱");
            }
            // Пустое пространство
            else {
                printf(".");
            }
        }
        printf("\n");
    }
}

void move_snake(int snake_length, Point* snake) {
    for (int i = snake_length - 1; i > 0; i--) {
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
    }
    snake[0].x++;
    if (snake[0].x > width - 2) {
        snake[0].x = 1;
    }
}

void init_snake(int snake_length, Point* snake) {
    snake[0].y = rand() % (height - 2) + 1;
    snake[0].x = rand() % (width - 2) + 1;
    for (int i = 1; i < snake_length; ++i) {
        snake[i].y = snake[i - 1].y;
        snake[i].x = snake[i - 1].x - 1;
    }
}

int main() {
    // Включаем поддержку UTF-8 в консоли Windows
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Скрываем курсор, чтобы не маячил
    HANDLE q = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cur;
    GetConsoleCursorInfo(q, &cur);
    cur.bVisible = FALSE;
    SetConsoleCursorInfo(q, &cur);

    int snake_length = 3;
    srand(time(NULL));

    Point* snake = malloc(snake_length * sizeof(Point));
    if (snake == NULL) {
        return 1;
    }

    init_snake(snake_length, snake);

    // Очистим консоль один раз в начале
    system("cls");

    while (true) {
        move_snake(snake_length, snake);
        draw_game(snake_length, snake);
        Sleep(100);
    }

    free(snake);
    return 0;
}