#ifndef GAME_H
#define GAME_H


#include <stdlib.h>


typedef int sudoku_width;
typedef char sudoku_char;
typedef sudoku_char* sudoku_field;

typedef struct Game {
    sudoku_width field_size;
    sudoku_field field;
    sudoku_field initial_field;
} Game;

Game* game_init(sudoku_width field_size, int prefill_n);
void game_run(Game *game);
void game_solve(Game *game);
void game_clean(Game *game);

#endif // GAME_H