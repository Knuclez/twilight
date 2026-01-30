#ifndef SCREEN_H
#define SCREEN_H
#include <SDL2/SDL.h>

void screen_entity_clicked(int id_ent);
void screen_text_event(SDL_Event event);
void screen_present(SDL_Renderer *renderer, float delta);
void screen_init();
#endif
