#include "game.h"
#include "aux.h"

Game* game_init(sudoku_width field_size) {
    Game *game = malloc(sizeof(Game));
    game->field = calloc(field_size*field_size, sizeof(sudoku_char));
    game->field_size = field_size;
    return game;
}

void game_start(Game *game) {
    print_game(game);
    set_cursor_position(1, 1);
    scanf("%d");
}

void game_clean(Game *game) {
    free(game->field);
    free(game);
}