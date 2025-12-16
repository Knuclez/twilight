#include <SDL2/SDL.h>

#include "interface/rendering/render_auxs.h"


void center_rect_x(SDL_Window *window, SDL_Rect *rect){
    int w = 0;
    int h = 0;
    SDL_GetWindowSize(window, &w, &h);
    int w_half = w /2;
    int rect_w_half = (rect->w) /2;
    rect->x = w_half - rect_w_half;
}

void color_to_white(SDL_Color *color){
    color->r = 255;
    color->g = 255;
    color->b = 255;
}
