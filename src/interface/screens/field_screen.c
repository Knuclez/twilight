#include <SDL2/SDL.h>
#include <stdio.h>

#include "interface/rendering/texturing.h"
#include "interface/screens/field_screen.h"
#include "interface/rendering/render_auxs.h"
#include "ecs/direction_ecs.h"
#include "ecs/position_ecs.h"
#include "ecs/size_ecs.h"
#include "ecs/source_rect_ecs.h"
#include "ecs/is_drawable_ecs.h"

SDL_Texture *big_atlas;

void field_screen_entity_clicked(int id_ent, SDL_Event event){
    return;
}

void field_screen_key_event(SDL_Event event){
    return;
}

void field_screen_input_event(SDL_Event event){
    return;
}

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

void draw_cow(SDL_Renderer *r, int id){
    Position *pos = get_id_associated_position(id);
    Size *size = get_id_associated_size(id);
    Direction *dir = get_id_associated_direction(id);
    SDL_Rect rect = {pos->x, pos->y, size->w, size->h};
    int sprite_selector = 64 * (*dir);
    SDL_Rect source_rect = {66 + sprite_selector, 0, 64, 64};
    SDL_RenderCopy(r, big_atlas, &source_rect, &rect);
}


void draw_grass(SDL_Renderer *r, int id){
    Position *pos = get_id_associated_position(id);
    if (pos == NULL){
	return;
    }
    Size *size = get_id_associated_size(id);
    if (size == NULL){
	return;
    }
    SDL_Rect rect = {pos->x, pos->y, size->w, size->h};
    SDL_Rect source_rect = {0, 67, 64, 64};
    SDL_RenderCopy(r, big_atlas, &source_rect, &rect);
}

void draw_tree(SDL_Renderer *r, int id){
    Position *pos = get_id_associated_position(id);
    Size *size = get_id_associated_size(id);
    SDL_Rect rect = {pos->x, pos->y, size->w, size->h};
    SDL_Rect source_rect = {67, 67, 64, 64};
    SDL_RenderCopy(r, big_atlas, &source_rect, &rect);
}

void draw_entities(SDL_Renderer *renderer){
    int drawables_amount = get_drawable_comp_amount();
    int* drawables = get_drawables();
    for(int i = 0; i < drawables_amount; i++){
	int drawable_id = *(drawables + i);
	if(drawable_id == -1){
	    continue;
	}
	draw_entity(renderer, drawable_id);
    }
}

void present_field_screen(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, 0, 210, 0, 255);
    SDL_RenderClear(renderer);


    draw_entities(renderer);
    //draw_cow(renderer, 102);
    //draw_entity(renderer, 103);
    //draw_grass(renderer, 104);
    //draw_cloud(renderer);
    //draw_tree(renderer, 105);
    SDL_RenderPresent(renderer);
}

//void append_new_entity(SDL_Texture *txt, int id, int z, unsigned char flags)
//por motivos de agilidad y testeo voy a harcodear los IDs(es decir machearlos a los que declaro
//en mi load_ents() de screen.c) pero despues tendria que hacer un loader o algo dinmaico
void init_field_screen(){
    big_atlas = get_texture_by_index(0);
    return;
}
