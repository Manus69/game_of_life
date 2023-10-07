#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

#define BSIZE   100
#define DEAD    0
#define ALIVE   1

typedef unsigned char   cell_t;
typedef struct Board    Board;

struct Board
{
    cell_t cells[BSIZE][BSIZE];
};

Board   Board_new(void);
bool    Board_cell_alive(const Board * board, int row, int col);
void    Board_cell_kill_all(Board * board);
void    Board_cell_toggle(Board * board, int row, int col);
void    Board_next(Board * board);

#endif