#ifndef EDITOR_H
#define EDITOR_H

#include <SDL2/SDL.h>
#include "interface/UI/ui_button.h"

#define IS_EDITOR_ACTIVE 	0b00000000000000000000000000000001
#define IS_GAME_RUNNING 	0b00000000000000000000000000000010

typedef struct {
    int          editor_bitmask;
    UIButtonList buttons;         /* botones estaticos (Pause, Save, etc.) */
    UIButtonList entity_buttons;  /* botones dinamicos de entidades */
}EditorState;

void init_editor();
EditorState* get_editor();
int  editor_is_active();
void editor_toggle();
void editor_update(float delta);
void editor_render(SDL_Renderer *renderer);
void editor_interpret_key_event(SDL_Event event);
void editor_mouse_button_clicked(SDL_Event event);

#endif
