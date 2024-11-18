#ifndef GAME_H
#define GAME_H


#include <stdlib.h>


typedef size_t sudoku_width;
typedef char sudoku_char;
typedef sudoku_char* sudoku_field;

typedef struct Game {
    sudoku_width field_size;
    sudoku_field field;
} Game;

Game* game_init(sudoku_width field_size);
void game_start(Game *game);
void game_solve(Game *game);
void game_clean(Game *game);

#endif // GAME_H