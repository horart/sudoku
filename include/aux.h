#ifndef AUX_H
#define AUX_H

#include "game.h"

#define KEY_ARROW_UP 65
#define KEY_ARROW_DOWN 66
#define KEY_ARROW_LEFT 68
#define KEY_ARROW_RIGHT 67

typedef struct Cursor {
    sudoku_width row;
    sudoku_width col;
} Cursor;

typedef struct Delta {
    int x;
    int y;
} Delta;

sudoku_char *get_cell_ptr(Game *game, sudoku_width row, sudoku_width col);

Cursor* get_cursor(void);
void update_game(Game *game, Cursor *cursor);
void carriage_to_end(int lines_put);
void set_cursor_position(Cursor *cursor, sudoku_width row, sudoku_width col);

int wait_for_key(void);
int is_num_key(int key);
int is_arrow_key(int key);
int key_to_num(int key);
void move_cursor_by_key(Cursor *cursor, int key, sudoku_width max_d);

#endif // AUX_H