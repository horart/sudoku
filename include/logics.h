#ifndef LOGICS_H
#define LOGICS_H

int find_middle_divisor(sudoku_width sf);

int is_valid_field(Game *game);

int check_for_win(Game *game);

void prefill(Game *game, int number_given);

#endif // LOGICS_H