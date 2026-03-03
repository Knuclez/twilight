#include <stdio.h>
#include <SDL2/SDL.h>

#include "interface/rendering/texturing.h"
#include "editor.h"
#include "entities.h"
#include "game_state.h"

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

void editor_mouse_button_clicked(SDL_Event event){
    printf("button clicked in editor\n");
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
    int panel_h = h / 2;
    SDL_SetRenderDrawColor(renderer, 250, 250, 250, 255);
    SDL_Rect panel = {w - panel_w, 0, panel_w, panel_h};
    SDL_RenderFillRect(renderer, &panel);
    int row_h = 20;
    int row = 0;
    for(int i = 0; i < max_ents; i++){
	if(entities[i].key.index == 0){continue;}
	char s[50];
	snprintf(s, sizeof(s), "index: %d", entities[i].key.index);
	SDL_Texture *txt = instance_dynamic_text_texture(renderer, s);
	SDL_Rect output_rect = {panel.x + 5, panel.y + 5 + (row * row_h), panel.w - 10, row_h - 2};
	SDL_RenderCopy(renderer, txt, NULL, &output_rect);
	row++;
    }
}

void init_editor(){
    editor_state.editor_bitmask |= IS_GAME_RUNNING;
}
