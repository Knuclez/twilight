#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "editor/editor_main.h"
#include "entities.h"
#include "game_state.h"
#include "save_load.h"
#include "interface/UI/ui_button.h"
#include "interface/UI/ui_input_field.h"

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

static void on_submit_pos_x(const char *text){
    EditorState *es = get_editor();
    Entity *ent = &get_game_state_p()->entities[es->inspected_entity.index];
    if (ent->key.generation != es->inspected_entity.generation) return;
    ent->position.x = atoi(text);
    ent->physical_bounds.x = ent->position.x;
}

static void on_submit_pos_y(const char *text){
    EditorState *es = get_editor();
    Entity *ent = &get_game_state_p()->entities[es->inspected_entity.index];
    if (ent->key.generation != es->inspected_entity.generation) return;
    ent->position.y = atoi(text);
    ent->physical_bounds.y = ent->position.y;
}

static void on_submit_health(const char *text){
    EditorState *es = get_editor();
    Entity *ent = &get_game_state_p()->entities[es->inspected_entity.index];
    if (ent->key.generation != es->inspected_entity.generation) return;
    ent->health = atoi(text);
}

void btn_entity_selected(int index){
    printf("[editor] entidad seleccionada: index %d\n", index);
    Entity *entities = get_game_state_p()->entities;
    Entity ent = entities[index];
    editor_state.editor_bitmask |= IS_INSPECTING_ENTITY;
    editor_state.inspected_entity = ent.key;

    /* Rebuild inspector input fields (once per selection, not every frame). */
    ui_input_field_list_init(&editor_state.input_fields);
    ui_text_label_list_init(&editor_state.text_labels);
    ui_text_label_add(&editor_state.text_labels, (SDL_Rect){10,  70, 120, 24}, "texto");
    ui_input_field_add(&editor_state.input_fields, (SDL_Rect){10,  98, 120, 24}, on_submit_pos_x);
    ui_input_field_add(&editor_state.input_fields, (SDL_Rect){10,  126, 120, 24}, on_submit_pos_y);
    ui_input_field_add(&editor_state.input_fields, (SDL_Rect){10, 154, 120, 24}, on_submit_health);
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
        ui_input_field_handle_click(&editor_state.input_fields, event.button.x, event.button.y);
    }
}

void editor_interpret_key_event(SDL_Event event){
    /* When a field is focused, route keys to it first. */
    if (editor_state.editor_bitmask & IS_READING_INPUT){
        ui_input_field_handle_key(&editor_state.input_fields, event.key.keysym.sym);
        return;
    }
    if (event.key.keysym.sym == SDLK_p){
	editor_state.editor_bitmask ^= IS_GAME_RUNNING;
	printf("game is now %s\n", editor_state.editor_bitmask & IS_GAME_RUNNING ? "RESUMED" : "PAUSED");
	return;
    }
}

void editor_text_input(SDL_Event event){
    if (editor_state.editor_bitmask & IS_READING_INPUT)
        ui_input_field_handle_text(&editor_state.input_fields, event.text.text);
}

void init_editor(){
    editor_state.editor_bitmask = IS_GAME_RUNNING;
    ui_button_list_init(&editor_state.buttons);
    ui_button_list_init(&editor_state.entity_buttons);
    ui_input_field_list_init(&editor_state.input_fields);
    ui_button_add(&editor_state.buttons, (SDL_Rect){10, 10, 80, 24}, "Pause", btn_toggle_pause);
    ui_button_add(&editor_state.buttons, (SDL_Rect){10, 40, 80, 24}, "Save",  btn_save);
}
