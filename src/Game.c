#include "Game.h"
#include <stdlib.h>

#define NAME        "Game of Life"
#define RES_DEFAULT 1000
#define PPC         (RES_DEFAULT / BSIZE)
#define TFT         (1000 / 60)
#define DELAY       200
#define PAUSE_BTN   SDLK_SPACE
#define CLEAR_BTN   SDLK_c
#define QUIT_BTN    SDLK_ESCAPE

static SDL_Color clr_bg_paused = (SDL_Color) {192, 192, 192, 255};
static SDL_Color clr_bg_running = (SDL_Color) {255, 128, 100, 255};
static SDL_Color clr_cell = (SDL_Color) {0, 0, 0, 255};

static inline void _get_resolution(int * w, int * h)
{
    * w = RES_DEFAULT;
    * h = RES_DEFAULT;
}

Game Game_init(void)
{
    int width, height;
    Gui gui;

    _get_resolution(& width, & height);
    gui = Gui_init(NAME, width, height);
    if (Gui_check(& gui) == GUI_STATUS_FUCKED) exit(EXIT_FAILURE);

    return (Game)
    {
        .gui = gui,
        .board = Board_new(),
        .running = true,
        .paused = true,
    };
}

void Game_quit(Game * game)
{
    Gui_kill(& game->gui);
}

static inline void _pause_toggle(Game * game)
{
    game->paused = ! game->paused;
}

static inline void _stop(Game * game)
{
    game->running = false;
}

static void _click(Game * game)
{
    int x, y;
    int row, col;

    SDL_GetMouseState(& x, & y);
    row = y / PPC;
    col = x / PPC;
    Board_cell_toggle(& game->board, row, col);
}

static void _process_input(Game * game)
{
    SDL_Event event;

    SDL_PollEvent(& event);
    if (event.type == SDL_QUIT) return _stop(game);
    if (event.type == SDL_MOUSEBUTTONDOWN && game->paused) return _click(game);
    if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.sym == QUIT_BTN) return _stop(game);
        if (event.key.keysym.sym == PAUSE_BTN) return _pause_toggle(game);
        if (event.key.keysym.sym == CLEAR_BTN) return Board_cell_kill_all(& game->board);
    }
}

static void _next_board(Game * game)
{
    if (game->paused) return;

    Board_next(& game->board);
}

static void _color_cells(Game * game)
{
    int x, y;

    for (int row = 0; row < BSIZE; row ++)
    {
        for (int col = 0; col < BSIZE; col ++)
        {
            if (Board_cell_alive(& game->board, row, col))
            {
                y = row * PPC;
                x = col * PPC;
                Gui_draw_square(& game->gui, x, y, PPC, clr_cell);
            }
        }
    }
}

static void _update_screen(Game * game)
{
    SDL_Color clr;

    clr = game->paused ? clr_bg_running : clr_bg_paused;
    Gui_set_color(& game->gui, clr);
    Gui_fill(& game->gui, clr);
    _color_cells(game);
    Gui_render(& game->gui);
}

void Game_run(Game * game)
{
    while (true)
    {
        _process_input(game);
        if (! game->running) return ;
        if (! game->paused) SDL_Delay(DELAY);
        _next_board(game);
        _update_screen(game);
    }
}