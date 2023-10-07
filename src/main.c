#include "Game.h"

int main()
{
    Game game;

    game = Game_init();
    Game_run(& game);
    Game_quit(& game);

    return 0;
}
