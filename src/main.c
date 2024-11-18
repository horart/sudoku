#include <stdio.h>
#include <unistd.h>
#include "config.c"
#include "game.h"


#define SIZE 5


int main() {
    printf("Enter your preffered sudoku size [default is %d]: ", SUDOKU_FIELD_SIZE_DEFAULT);
    sudoku_width field_size = SUDOKU_FIELD_SIZE_DEFAULT;
    scanf("%d", &field_size);
    printf("Prefilled cells count [default is %d]: ", SUDOKU_PREFILLED_DEFAULT);
    int prefilled_n = SUDOKU_PREFILLED_DEFAULT;
    scanf("%d", &prefilled_n);
    Game *game = game_init(field_size, prefilled_n);
    #ifndef ENABLE_AI
        game_run(game);
    #else
        game_solve(game);
    #endif
    game_clean(game);
    return 0;
}