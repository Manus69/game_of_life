#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Gui.h"

typedef struct Game Game;

struct Game
{
    Board   board;
    Gui     gui;
    bool    running;
    bool    paused;
};

Game Game_init(void);
void Game_quit(Game * game);
void Game_run(Game * game);

#endif