#ifndef GUI_H
#define GUI_H

#include <SDL2/SDL.h>

#define GUI_STATUS_FUCKED   -1
#define GUI_STATUS_OK       0
#define GUI_IMG             "test.png"


typedef struct Gui Gui;

struct Gui
{
    SDL_Window *    window;
    SDL_Renderer *  rendr;
    SDL_Texture *   texture;
    SDL_Rect        t_rect;
};

Gui     Gui_init(const char * w_name, int width, int height);
int     Gui_check(const Gui * gui);
void    Gui_kill(Gui * gui);
void    Gui_set_color(Gui * gui, SDL_Color color);
void    Gui_fill(Gui * gui, SDL_Color color);
void    Gui_draw_square(Gui * gui, int x, int y, int size, SDL_Color color);
void    Gui_render(Gui * gui);

#endif