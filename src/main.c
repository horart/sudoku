#include <stdio.h>
#include <unistd.h>
#include "config.c"
#include "game.h"


#define SIZE 5


int main() {
    printf("Enter your preffered sudoku size [default is %d]: ", SUDOKU_FIELD_SIZE_DEFAULT);
    sudoku_width field_size = SUDOKU_FIELD_SIZE_DEFAULT;
    scanf("%lu", &field_size);
    Game *game = game_init(field_size);
    #ifndef ENABLE_AI
        game_start(game);
    #else
        game_solve(game);
    #endif
    game_clean(game);
    return 0;
}