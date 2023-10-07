#include "Gui.h"

Gui Gui_init(const char * w_name, int width, int height)
{
    Gui gui = {};

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return gui;
    gui.window = SDL_CreateWindow
    (
        w_name,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );
    gui.rendr = SDL_CreateRenderer(gui.window, -1, 0);

    return gui;
}

int Gui_check(const Gui * gui)
{
    if (gui->window && gui->rendr) return GUI_STATUS_OK;

    return GUI_STATUS_FUCKED;
}

void Gui_kill(Gui * gui)
{
    SDL_DestroyRenderer(gui->rendr);
    SDL_DestroyWindow(gui->window);
    SDL_Quit();
}

void Gui_set_color(Gui * gui, SDL_Color color)
{
    SDL_SetRenderDrawColor(gui->rendr, color.r, color.g, color.b, color.a);
}

void Gui_fill(Gui * gui, SDL_Color color)
{
    Gui_set_color(gui, color);
    SDL_RenderClear(gui->rendr);
}

void Gui_draw_square(Gui * gui, int x, int y, int size, SDL_Color color)
{
    SDL_Rect square;

    square = (SDL_Rect) {x, y, size, size};
    Gui_set_color(gui, color);
    SDL_RenderFillRect(gui->rendr, & square);
}

void Gui_render(Gui * gui)
{
    SDL_RenderPresent(gui->rendr);
}