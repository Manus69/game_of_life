#include "Board.h"
#include <string.h>

Board Board_new(void)
{
    return (Board)
    {
        .cells = {}
    };
}

const cell_t * Board_cell_get(const Board * board, int row, int col)
{
    return & board->cells[row][col];
}

bool Board_cell_alive(const Board * board, int row, int col)
{
    return * Board_cell_get(board, row, col) == ALIVE;
}

bool Board_cell_alive_check(const Board * board, int row, int col)
{
    if (row < 0 || row >= BSIZE) return false;
    if (col < 0 || col >= BSIZE) return false;

    return Board_cell_alive(board, row, col);
}

bool Board_cell_dead(const Board * board, int row, int col)
{
    return * Board_cell_get(board, row, col) == DEAD;
}

void Board_cell_kill(Board * board, int row, int col)
{
    board->cells[row][col] = DEAD;
}

void Board_cell_kill_all(Board * board)
{
    for (int row = 0; row < BSIZE; row ++)
    {
        for (int col = 0; col < BSIZE; col ++)
        {
            board->cells[row][col] = DEAD;
        }
    }
}

void Board_cell_revive(Board * board, int row, int col)
{
    board->cells[row][col] = ALIVE;
}

void Board_cell_toggle(Board * board, int row, int col)
{
    board->cells[row][col] = ! board->cells[row][col];
}

int Board_cell_count_neighbours(const Board * board, int row, int col)
{
    int count;

    count = Board_cell_alive(board, row, col) ? -1 : 0;
    for (int row_d = -1; row_d < 2; row_d ++)
    {
        for (int col_d = -1; col_d < 2; col_d ++)
        {
            count += Board_cell_alive_check(board, row + row_d, col + col_d);
        }
    }

    return count;
}

static inline cell_t _decide_fate(cell_t cell, int neighbours)
{
    if (cell == DEAD) return neighbours == 3 ? ALIVE : DEAD;
    if (neighbours < 2) return DEAD;
    if (neighbours > 3) return DEAD;

    return ALIVE;
}

void Board_next(Board * board)
{
    cell_t  cells[BSIZE][BSIZE];
    int     neighbours;

    for (int row = 0; row < BSIZE; row ++)
    {
        for (int col = 0; col < BSIZE; col ++)
        {
            neighbours = Board_cell_count_neighbours(board, row, col);
            cells[row][col] = _decide_fate(board->cells[row][col], neighbours);
        }
    }

    memcpy(board->cells, cells, sizeof(cell_t) * BSIZE * BSIZE);
}