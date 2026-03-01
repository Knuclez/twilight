#ifndef INPUT_HANDLER
#define INPUT_HANDLER
#include <SDL2/SDL.h>

void event_key_down_handle(SDL_Event event);
void event_key_up_handle(SDL_Event event);
void controller_axis_interpret(int x_axis, int y_axis);

#endif
