#include "game.h"
#include "ai.h"
#include "aux.h"
#include "logics.h"
#include <unistd.h>
#include "config.c"
#include <memory.h>
#include <stdio.h>


int solve(Game *game, Cursor *cursor, int idx) {
    memcpy(game->field+idx, game->initial_field+idx, (game->field_size*game->field_size-idx)*sizeof(sudoku_char));
    cursor->row = (idx) / game->field_size;
    cursor->col = (idx) % game->field_size;
    update_game(game, cursor);
    if(*(game->initial_field+idx)) {
        return solve(game, cursor, idx+1);
    }
    if(idx == game->field_size*game->field_size) {
        return 1;
    }
    for(int i = 1; i <= game->field_size; i++) {
        sudoku_char old = *(game->field+idx);
        *(game->field+idx) = i;
        if(!is_valid_field(game)) {
            *(game->field+idx) = old;
            continue;
        }
        usleep(AI_DELAY_MS*1000);
        if(solve(game, cursor, idx+1)) {
            return 1;
        }
        else {
            *(game->field+idx) = old;
        }
    }
    return 0;
}


void game_solve(Game *game) {
    Cursor *cursor = get_cursor();
    cursor->col = 0;
    cursor->row = 0;
    solve(game, cursor, 0);
    update_game(game, cursor);
    carriage_to_end(game->field_size);
    printf("AI WON!!!\n");
}