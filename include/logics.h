/// @file
/// @brief File with core logics of the sudoku game

#ifndef LOGICS_H
#define LOGICS_H

/// @brief Find the closest from the bottom divisor to `sqrt(sf)`
/// @return 
int find_middle_divisor(sudoku_width sf);

/// @brief check if current game field contains duplicates within rows, columns, or tiles
/// @param game the game field of which is to be checked
/// @return 1 if no duplicates, 0 if there are
int is_valid_field(Game *game);

/// @brief check if current game is won (field is full with no duplicates)
/// @param game the game field of which is to be checked
/// @return 1 if won, 0 if the game goes on
int check_for_win(Game *game);

/// @brief prefill random `number_given` cells with random values valid for the `game->field_width`
/// @param game 
/// @param number_given how many cells to initialize with random values
void prefill(Game *game, int number_given);

#endif // LOGICS_H