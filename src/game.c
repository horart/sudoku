#include "game.h"
#include "aux.h"
#include <stdio.h>
#include "logics.h"

Game* game_init(sudoku_width field_size, int prefill_n) {
    Game *game = malloc(sizeof(Game));
    game->field = calloc(field_size*field_size, sizeof(sudoku_char));
    game->field_size = field_size;
    game->initial_field = calloc(field_size*field_size, sizeof(sudoku_char));
    // prefill BOTH ARRAYS
    prefill(game, prefill_n);
    return game;
}

void game_run(Game *game) {
    Cursor *cursor = get_cursor();
    cursor->col = 0;
    cursor->row = 0;
    update_game(game, cursor);
    while(1) {
        int key = wait_for_key();
        if(is_arrow_key(key)) {
            move_cursor_by_key(cursor, key, game->field_size);
        }
        else if(is_num_key(key)) {
            if(!*(game->initial_field + cursor->row*game->field_size + cursor->col)) {
                *get_cell_ptr(game, cursor->row, cursor->col) = key_to_num(key);
            }
        }
        else {
            continue;
        }
        if(check_for_win(game)) {
            update_game(game, cursor);
            carriage_to_end(game->field_size);
            printf("YOU WIN!!! Press any key...\n");
            wait_for_key();
            break;
        }
        update_game(game, cursor);
    }
    free(cursor);
}

void game_clean(Game *game) {
    free(game->field);
    free(game->initial_field);
    free(game);
}