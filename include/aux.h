/// @file
/// @brief I/O functions mainly

#ifndef AUX_H
#define AUX_H

#include "game.h"

#define KEY_ARROW_UP 65
#define KEY_ARROW_DOWN 66
#define KEY_ARROW_LEFT 68
#define KEY_ARROW_RIGHT 67

/// @brief Struct used to track cursor location relative to top-left corner of the sudoku field
typedef struct Cursor {
    sudoku_width row;
    sudoku_width col;
} Cursor;

/// @brief translates row and column of the field to pointer in the field blob referring to the value of the cell
/// @param game The field with corresponding row and column
/// @param row cell row (0-based)
/// @param col cell column (0-based)
/// @return pointer to cell value
sudoku_char *get_cell_ptr(Game *game, sudoku_width row, sudoku_width col);

/// @brief simple constructor
/// @return uninitialized cursor on the heap
Cursor* get_cursor(void);


/// @brief Rerender the whole game according to the `game->field` and cursor position provided
/// @param game 
/// @param cursor
void update_game(Game *game, Cursor *cursor);


/// @brief Put the carriage to the last line first column
/// @param lines_put lines already put (in case of a game, `game->field_size`)
void carriage_to_end(int lines_put);


/// @brief wrapper around termios to block until user presses a key
/// @return key id
int wait_for_key(void);


/// @brief is given key id id of a number 0-9?
/// @param key key id
/// @return 1 if yes, 0 if not
int is_num_key(int key);


/// @brief is given key id id of an arrow key?
/// @param key key id
/// @return 1 if yes, 0 if not
int is_arrow_key(int key);


/// @brief convert key id of number to int
/// @param key got to be a valid number key id, otherwise the behaviour is undefined
/// @return 1-9 int
int key_to_num(int key);


/// @brief increment/decrement cursor x and y position
/// @note this function DOES NOT cause any rerender. In order to see the changes, call `update_game` afterwards
/// @param cursor 
/// @param key 
/// @param max_d 
void move_cursor_by_key(Cursor *cursor, int key, sudoku_width max_d);

#endif // AUX_H