#include <stdio.h>
#include "game.h"


sudoku_char* get_cell(Game *game, sudoku_width row, sudoku_width col) {
    return game->field + game->field_size*row + col;
}


void print_game(Game *game) {
    for(int r = 0; r < game->field_size; r++) {
        for(int c = 0; c < game->field_size; c++) {
            sudoku_char gc = *get_cell(game, r, c);
            if(gc != 0) {
                printf("%c ", '0'+gc);
            }
            else {
                printf(". ");
            }
        }
        printf("\n");
    }
}

void set_cursor_position(sudoku_width row, sudoku_width col) {
    printf("\033[%lu;%luH", row + 3, (col + 1) * 2 - 1 );
}