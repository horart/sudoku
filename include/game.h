/// @file
/// @brief Header for the game abstraction

#ifndef GAME_H
#define GAME_H


#include <stdlib.h>


typedef int sudoku_width;
typedef char sudoku_char;
/// @brief an array of numbers from zero to field_size. Zero means the place is empty
typedef sudoku_char* sudoku_field;


/// @brief struct of a sudoku game
typedef struct Game {
    /// @brief length of side of the square. This also serves as inner rectangles number and as the maximum `sudoku_char` value
    sudoku_width field_size;
    /// @brief a contigious array on the heap, row-major ordered. Value zero means no number in the cell yet.
    sudoku_field field;
    /// @brief the field with prefilled values. `readonly`
    sudoku_field initial_field;
} Game;

/// @brief Initialize a game struct with allocated `field` and `initial_field`. Prefill both those arrays.
/// @param field_size
/// @param prefill_n number of cells to be filled
/// @note You are responsible to call game_clean later. Calling `free(game)` will cause memory leaks.
/// @return 
Game* game_init(sudoku_width field_size, int prefill_n);


/// @brief pass the flow to the interactive game to interact with the user
/// @warning terminal WILL BE cleared
/// @param game the game object with initialized fields
void game_run(Game *game);


/// @brief Free the memory used by the game
/// @param game Game to be deleted
void game_clean(Game *game);

#endif // GAME_H