#include <stdio.h>
#include "game.h"
#include <termios.h>
#include <unistd.h>
#include "aux.h"


sudoku_char* get_cell_ptr(Game *game, sudoku_width row, sudoku_width col) {
    return game->field + game->field_size*row + col;
}


Cursor* get_cursor(void) {
    Cursor *cursor = malloc(sizeof(Cursor));
    return cursor;
}

void update_game(Game *game, Cursor *cursor) {
    printf("\033[H\033[J");
    for(int r = 0; r < game->field_size; r++) {
        for(int c = 0; c < game->field_size; c++) {
            sudoku_char gc = *get_cell_ptr(game, r, c);
            if(gc != 0) {
                printf(" %c", '0'+gc);
            }
            else {
                printf(" .");
            }
        }
        printf("\n");
    }
    
    printf("\033[%d;%dH[", cursor->row + 1, (cursor->col + 1) * 2 - 1);
    printf("\033[%d;%dH]", cursor->row + 1, (cursor->col + 1) * 2 + 1);
    printf("\033[%d;%dH\n", cursor->row + 1, (cursor->col + 1) * 2 );
}

void carriage_to_end(int lines_put) {
    printf("\033[%d;%dH", lines_put + 1, 0);
}

int wait_for_key(void) {
    int ch;
    struct termios oldt;
    struct termios newt;
    tcgetattr(STDIN_FILENO, &oldt); /*store old settings */
    newt = oldt; /* copy old settings to new settings */
    newt.c_lflag &= ~(ICANON | ECHO); /* make one change to old settings in new settings */
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); /*apply the new settings immediatly */
    ch = getchar(); /* standard getchar call */
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); /*reapply the old settings */
    return ch; /*return received char */
}

int is_num_key(int key) {
    if(key >= 48 && key <= 57) {
        return 1;
    }
    return 0;
}

int is_arrow_key(int key) {
    if(key == KEY_ARROW_UP || key == KEY_ARROW_DOWN || key == KEY_ARROW_LEFT || key == KEY_ARROW_RIGHT) {
        return 1;
    }
    return 0;
}

int key_to_num(int key) {
    return key - 48;
}

sudoku_width min(sudoku_width a, sudoku_width b) {
    return a < b ? a : b;
}

sudoku_width max(sudoku_width a, sudoku_width b) {
    return a > b ? a : b;
}

void move_cursor_by_key(Cursor *cursor, int key, sudoku_width max_d) {
    if(key == KEY_ARROW_DOWN) {
        cursor->row = min(cursor->row+1, max_d-1);
    }
    if(key == KEY_ARROW_UP) {
        cursor->row = max(cursor->row-1, 0);
    }
    if(key == KEY_ARROW_LEFT) {
        cursor->col = max(cursor->col-1, 0);
    }
    if(key == KEY_ARROW_RIGHT) {
        cursor->col = min(cursor->col+1, max_d-1);
    }
}