#ifndef EDITOR_H
#define EDITOR_H

#include <SDL2/SDL.h>
#include "entities.h"
#include "interface/UI/ui_button.h"
#include "editor/editor_rendering.h"

#define IS_EDITOR_ACTIVE 	0b00000000000000000000000000000001
#define IS_GAME_RUNNING 	0b00000000000000000000000000000010
#define IS_INSPECTING_ENTITY 	0b00000000000000000000000000000100

typedef struct {
    int          editor_bitmask;
    UIButtonList buttons;         /* botones estaticos (Pause, Save, etc.) */
    UIButtonList entity_buttons;  /* botones dinamicos de entidades */
    EntityKey inspected_entity;
}EditorState;

void init_editor();
EditorState* get_editor();
int  editor_is_active();
void editor_toggle();
void editor_update(float delta);
void btn_entity_selected(int index);
void editor_interpret_key_event(SDL_Event event);
void editor_mouse_button_clicked(SDL_Event event);

#endif
