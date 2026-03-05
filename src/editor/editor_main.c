#include <stdio.h>
#include <SDL2/SDL.h>

#include "editor/editor_main.h"
#include "entities.h"
#include "game_state.h"
#include "save_load.h"
#include "interface/UI/ui_button.h"

EditorState editor_state = {0};

EditorState* get_editor(){
    return &editor_state;
}

int editor_is_active(){
    if(editor_state.editor_bitmask & IS_EDITOR_ACTIVE){
	return 1;
    }
    return 0;
}

void editor_toggle(){
    editor_state.editor_bitmask = editor_state.editor_bitmask ^ IS_EDITOR_ACTIVE;
    printf("editor mode: %s\n", editor_state.editor_bitmask & IS_EDITOR_ACTIVE ? "ON" : "OFF");
}

/* Logica extra del editor por frame (mouse picking, drag, etc.)
   El juego sigue corriendo en paralelo. */
void editor_update(float delta){
    (void)delta;
    /* TODO: mouse picking, mover entidades, modificar componentes */
}

void btn_entity_selected(int index){
    printf("[editor] entidad seleccionada: index %d\n", index);
    /* TODO: abrir inspector de la entidad */
    Entity *entitites = get_game_state_p()->entities;
    Entity ent = entitites[index];
    editor_state.editor_bitmask |= IS_INSPECTING_ENTITY;
    editor_state.inspected_entity = ent.key;
}

static void btn_toggle_pause(void){
    editor_state.editor_bitmask ^= IS_GAME_RUNNING;
    printf("game is now %s\n", editor_state.editor_bitmask & IS_GAME_RUNNING ? "RESUMED" : "PAUSED");
}

static void btn_save(void){
    entities_save();
}

void editor_mouse_button_clicked(SDL_Event event){
    if (event.button.button == SDL_BUTTON_LEFT){
        ui_button_handle_click(&editor_state.buttons,        event.button.x, event.button.y);
        ui_button_handle_click(&editor_state.entity_buttons, event.button.x, event.button.y);
    }
}

void editor_interpret_key_event(SDL_Event event){
    if (event.key.keysym.sym == SDLK_p){
	editor_state.editor_bitmask ^= IS_GAME_RUNNING;
	printf("game is now %s\n", editor_state.editor_bitmask & IS_GAME_RUNNING ? "RESUMED" : "PAUSED");
	return;
    }
}

void init_editor(){
    editor_state.editor_bitmask = IS_GAME_RUNNING;
    ui_button_list_init(&editor_state.buttons);
    ui_button_list_init(&editor_state.entity_buttons);
    ui_button_add(&editor_state.buttons, (SDL_Rect){10, 10, 80, 24}, "Pause", btn_toggle_pause);
    ui_button_add(&editor_state.buttons, (SDL_Rect){10, 40, 80, 24}, "Save",  btn_save);
}
