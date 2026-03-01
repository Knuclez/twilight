#include <stdio.h>
#include <SDL2/SDL.h>

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
    GameState *gs = get_game_state_p();
    Entity *entities = gs->entities;
    Entity *ent;
    for(int i = 0; i < gs->max_index; i++){
	ent = &entities[i];
	if(ent->key.index == 0){continue;}
	if(!(ent->bitmask & IS_DRAWABLE_MASK)){continue;}
	//TODO ENTITY COLLISION CHECK
	if(left_side > r_s){
	    continue;
	}
	    right_side = to_check.position.x + to_check.physical_bounds.width + to_check.physical_bounds.x;
	    l_s = e.position.x - e.physical_bounds.width + to_check.physical_bounds.x;
	    if(right_side < l_s){
		continue;
	    }
	    top = to_check.position.y - to_check.physical_bounds.height + to_check.physical_bounds.y;
	    b = e.position.y + e.physical_bounds.height + to_check.physical_bounds.y;
	    if(top > b){
		continue;
	    }
	    bottom = to_check.position.y + to_check.physical_bounds.height + to_check.physical_bounds.y;
	    t = e.position.y - e.physical_bounds.height + to_check.physical_bounds.y;
	    if(bottom < t){
		continue;
	    }
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
    /* Borde rojo para indicar modo editor activo */
    SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
    SDL_Rect top    = {0,   0,   800, 4};
    SDL_Rect bottom = {0,   596, 800, 4};
    SDL_Rect left   = {0,   0,   4,   600};
    SDL_Rect right  = {796, 0,   4,   600};
    SDL_RenderFillRect(renderer, &top);
    SDL_RenderFillRect(renderer, &bottom);
    SDL_RenderFillRect(renderer, &left);
    SDL_RenderFillRect(renderer, &right);

    /* TODO: grilla, inspector de entidades, panel de propiedades, boton pause */
}

void init_editor(){
    editor_state.editor_bitmask |= IS_GAME_RUNNING;
}
