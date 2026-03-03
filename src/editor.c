#include <stdio.h>
#include <SDL2/SDL.h>

#include "interface/rendering/texturing.h"
#include "editor.h"
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

static void btn_entity_selected(int index){
    printf("[editor] entidad seleccionada: index %d\n", index);
    /* TODO: abrir inspector de la entidad */
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

/* Render del editor encima del juego: borde indicador, gizmos, paneles. */
void editor_render(SDL_Renderer *renderer){
    int w, h;
    SDL_GetRendererOutputSize(renderer, &w, &h);

    /* Borde rojo para indicar modo editor activo */
    int border = 4;
    SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
    SDL_Rect top    = {0,        0,        w,      border};
    SDL_Rect bottom = {0,        h-border, w,      border};
    SDL_Rect left   = {0,        0,        border, h};
    SDL_Rect right  = {w-border, 0,        border, h};
    SDL_RenderFillRect(renderer, &top);
    SDL_RenderFillRect(renderer, &bottom);
    SDL_RenderFillRect(renderer, &left);
    SDL_RenderFillRect(renderer, &right);

    /* TODO: grilla, inspector de entidades, panel de propiedades, boton pause */

    //QUIERO HACER UNA LISTA DE ENTIDADES EN ESTE COSTADITO
    GameState *gs = get_game_state_p();
    Entity *entities = gs->entities;
    int max_ents = gs->max_index;

    int panel_w = w / 4;
    int panel_x = w - panel_w;

    /* fondo del panel */
    SDL_SetRenderDrawColor(renderer, 40, 40, 40, 220);
    SDL_Rect panel_bg = {panel_x, 0, panel_w, h};
    SDL_RenderFillRect(renderer, &panel_bg);

    /* reconstruir botones de entidades cada frame */
    int row_h = 24;
    int margin = 4;
    ui_button_list_init(&editor_state.entity_buttons);
    int row = 0;
    for (int i = 0; i < max_ents; i++){
        if (entities[i].key.index == 0) continue;
        /* label estatico por slot: se guarda como string en una tabla local */
        static char labels[MAX_ENTITIES][32];
        snprintf(labels[i], sizeof(labels[i]), "[%d] ent", entities[i].key.index);
        SDL_Rect r = {panel_x + margin,
                      margin + row * (row_h + margin),
                      panel_w - margin * 2,
                      row_h};
        ui_button_add_with_data(&editor_state.entity_buttons, r, labels[i],
                                entities[i].key.index, btn_entity_selected);
        row++;
    }
    ui_button_render(&editor_state.entity_buttons, renderer);

    ui_button_render(&editor_state.buttons, renderer);
}

void init_editor(){
    editor_state.editor_bitmask = IS_GAME_RUNNING;
    ui_button_list_init(&editor_state.buttons);
    ui_button_list_init(&editor_state.entity_buttons);
    ui_button_add(&editor_state.buttons, (SDL_Rect){10, 10, 80, 24}, "Pause", btn_toggle_pause);
    ui_button_add(&editor_state.buttons, (SDL_Rect){10, 40, 80, 24}, "Save",  btn_save);
}
