#include "game.h"
#include "logics.h"
#include <malloc.h>
#include "aux.h"
#include <memory.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int find_middle_divisor(sudoku_width sf) {
    int m = round(sqrt((int) sf+1));
    for(; m > 0; m--) {
        if((int)sf%m == 0) {
            return m;
        }
    }
    return 0;
}

int is_valid_field(Game *game) {
    int *present = malloc(1+game->field_size*sizeof(int));

    for(int row = 0; row < game->field_size; row++) { // row check
        memset(present, 0, 1+game->field_size*sizeof(int));
        for(int col = 0; col < game->field_size; col++) {
            (*(present+*get_cell_ptr(game, row, col)))++;
        }
        for(int i = 1; i < 1 + game->field_size; i++) {
            if(*(present+i) > 1) {
                free(present);
                return 0;
            }
        }
    }

    for(int col = 0; col < game->field_size; col++) { // column check
        memset(present, 0, 1+game->field_size*sizeof(int));
        for(int row = 0; row < game->field_size; row++) {
            (*(present+*get_cell_ptr(game, row, col)))++;
        }
        for(int i = 1; i < 1 + game->field_size; i++) {
            if(*(present+i) > 1) {
                free(present);
                return 0;
            }
        }
    }

    for(int row = 0; row < game->field_size; row++) {
        memset(present, 0, 1+game->field_size*sizeof(int));
        for(int col = 0; col < game->field_size; col++) {
            (*(present+*get_cell_ptr(game, row, col)))++;
        }
        for(int i = 1; i < 1 + game->field_size; i++) {
            if(*(present+i) > 1) {
                free(present);
                return 0;
            }
        }
    }

    int md = find_middle_divisor(game->field_size);
    int md2 = game->field_size / md;

    for(int chunk_x = 0; chunk_x < game->field_size / md; chunk_x++) {
        for(int chunk_y = 0; chunk_y < game->field_size / md2; chunk_y++) {
            memset(present, 0, 1+game->field_size*sizeof(int));
            for(int row = chunk_y*md2; row < (chunk_y+1)*md2; row++) {
                for(int col = chunk_x*md; col < (chunk_x+1)*md; col++) {
                    (*(present+*get_cell_ptr(game, row, col)))++;
                }
            }
            for(int i = 1; i < 1 + game->field_size; i++) {
                if(*(present+i) > 1) {
                    free(present);
                    return 0;
                }
            }
        }
    }

    free(present);
    return 1;
}




int check_for_win(Game *game)
{

    int desired_sum = (1+game->field_size)*game->field_size/2;
    int sum;
    if(!is_valid_field(game)) {
        return 0;
    }

        for(int row = 0; row < game->field_size; row++) { // row check
        sum = 0;
        for(int col = 0; col < game->field_size; col++) {
            sum += *get_cell_ptr(game, row, col);
        }
        if(sum != desired_sum) {
            return 0;
        }
    }

    for(int col = 0; col < game->field_size; col++) { // column check
        sum = 0;
        for(int row = 0; row < game->field_size; row++) {
            sum += *get_cell_ptr(game, row, col);
        }
        if(sum != desired_sum) {
            return 0;
        }
    }

    for(int row = 0; row < game->field_size; row++) {
        sum = 0;
        for(int col = 0; col < game->field_size; col++) {
            sum += *get_cell_ptr(game, row, col);
        }
        if(sum != desired_sum) {
            return 0;
        }
    }

    int md = find_middle_divisor(game->field_size);
    int md2 = game->field_size / md;

    for(int chunk_x = 0; chunk_x < game->field_size / md; chunk_x++) {
        for(int chunk_y = 0; chunk_y < game->field_size / md2; chunk_y++) {
            sum = 0;
            for(int row = chunk_y*md2; row < (chunk_y+1)*md2; row++) {
                for(int col = chunk_x*md; col < (chunk_x+1)*md; col++) {
                    sum += *get_cell_ptr(game, row, col);
                }
            }
            if(sum != desired_sum) {
                return 0;
            }
        }
    }

    return 1;
}


void prefill(Game *game, int number_given) {
    time_t time_ = time(NULL);
    srand(time_);
    int ctr = 0;
    while(ctr < number_given) {
        int random_idx = rand() % (game->field_size*game->field_size);
        int random_val = rand() % game->field_size + 1;
        if(*(game->field + random_idx)) {
            continue;
        }
        *(game->field + random_idx) = random_val;
        if(!is_valid_field(game)) {
            *(game->field + random_idx) = 0;
            continue;
        }
        ctr++;
    }
    memcpy(game->initial_field, game->field, sizeof(sudoku_char)*game->field_size*game->field_size);
}