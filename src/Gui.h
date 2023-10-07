#ifndef GUI_H
#define GUI_H

#include <SDL2/SDL.h>

#define GUI_STATUS_FUCKED   -1
#define GUI_STATUS_OK       0

typedef struct Gui Gui;

struct Gui
{
    SDL_Window *    window;
    SDL_Renderer *  rendr;
};

Gui     Gui_init(const char * w_name, int width, int height);
int     Gui_check(const Gui * gui);
void    Gui_kill(Gui * gui);
void    Gui_set_color(Gui * gui, SDL_Color color);
void    Gui_fill(Gui * gui, SDL_Color color);
void    Gui_draw_square(Gui * gui, int x, int y, int size, SDL_Color color);
void    Gui_render(Gui * gui);

#endif