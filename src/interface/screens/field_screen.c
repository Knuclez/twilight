#include <SDL2/SDL.h>
#include <stdio.h>

#include "interface/rendering/texturing.h"
#include "interface/screens/field_screen.h"
#include "interface/rendering/render_auxs.h"
#include "scenes/field_scene.h"

#include "entities.h"
#include "components/position_comp.h"
#include "components/texture_indx_comp.h"

void field_screen_entity_clicked(int id_ent, SDL_Event event){
    return;
}

void field_screen_key_event(SDL_Event event){
    return;
}

void field_screen_input_event(SDL_Event event){
    return;
}

/*
void draw_entity(SDL_Renderer *r, int id){
    Position *pos = get_id_associated_position(id);
    Size *size = get_id_associated_size(id);
    Direction *dir = get_id_associated_direction(id);
    SourceRect *src_rct = get_id_associated_source_rect(id);
    int sprite_shift = 0;
    if(pos == NULL){
	return;
    }
    if(size == NULL){
	return;
    }
    if(dir != NULL){
	sprite_shift = 66 * (*dir);
    } 
    
    SDL_Rect rect = {pos->x, pos->y, size->w, size->h};
    SDL_Rect source_rect = {src_rct->x + sprite_shift, src_rct->y,  src_rct->w, src_rct->h};
    SDL_RenderCopy(r, big_atlas, &source_rect, &rect);
}

*/

void draw_entities(SDL_Renderer *r){
    EntityKey *ents = entities_get();
    int ents_amount = entities_amount();

    Position *positions = positions_get();
    int *textures = textures_index_get();
    for(int i = 0; i < ents_amount; i++){
	EntityKey key = *(ents + i);
	int bitmask = key.bitmask;

	if(bitmask & IS_DRAWABLE_MASK){
	    int pos_indx = position_index_get_from_key(key);
	    int txt_indx = texture_get_index_by_key(key);
	    SDL_Texture *txt = get_texture_by_index(txt_indx);
	    Position pos = *(positions + pos_indx);
	    SDL_Rect rect = {pos.x, pos.y, 130, 160};
	    SDL_Rect src_rect = {5, 84, 65, 81};
	    SDL_RenderCopy(r, txt, &src_rect, &rect);
	}
    }
}


void present_field_screen(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, 0, 210, 0, 255);
    SDL_RenderClear(renderer);


    draw_entities(renderer);
    SDL_RenderPresent(renderer);
}

//void append_new_entity(SDL_Texture *txt, int id, int z, unsigned char flags)
//por motivos de agilidad y testeo voy a harcodear los IDs(es decir machearlos a los que declaro
//en mi load_ents() de screen.c) pero despues tendria que hacer un loader o algo dinmaico
void init_field_screen(){
    return;
}
