#include <SDL2/SDL.h>
#include <stdio.h>

#include "interface/rendering/texturing.h"
#include "interface/screens/field_screen.h"
#include "interface/rendering/render_auxs.h"
#include "interface/rendering/gui_entities.h"
#include "ecs/direction_ecs.h"
#include "ecs/position_ecs.h"


void field_screen_entity_clicked(int id_ent, SDL_Event event){
    return;
}

void field_screen_key_event(SDL_Event event){
    return;
}

void field_screen_input_event(SDL_Event event){
    return;
}

void draw_cloud(SDL_Renderer *r){
    GUI_Entity *nub = get_entity_by_id(101);
    SDL_Rect rect = nub->rect;
    SDL_Rect source_rect = {0, 0, 64, 64};
    SDL_RenderCopy(r, nub->txt, &source_rect, &rect);
}

void draw_cow(SDL_Renderer *r, int id){
    GUI_Entity *ent = get_entity_by_id(id);
    Position *pos = get_id_associated_position(id);
    Direction *dir = get_id_associated_direction(id);
    SDL_Rect rect = {64, 64, pos->x, pos->y};
    //rect.x = pos->x;
    //rect.y = pos->y;
    int sprite_selector = 64 * (*dir);
    SDL_Rect source_rect = {66 + sprite_selector, 0, 64, 64};
    SDL_RenderCopy(r, ent->txt, &source_rect, &rect);
}


void draw_grass(SDL_Renderer *r, int id){
    GUI_Entity *grass = get_entity_by_id(id);
    SDL_Rect rect = grass->rect;
    SDL_Rect source_rect = {0, 67, 64, 64};
    SDL_RenderCopy(r, grass->txt, &source_rect, &rect);
}

void present_field_screen(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, 0, 210, 0, 255);
    SDL_RenderClear(renderer);

    draw_cow(renderer, 102);
    draw_cow(renderer, 103);
    draw_cloud(renderer);
    SDL_RenderPresent(renderer);
}

//void append_new_entity(SDL_Rect rect,SDL_Texture *txt, int id, int z, unsigned char flags)
//por motivos de agilidad y testeo voy a harcodear los IDs(es decir machearlos a los que declaro
//en mi load_ents() de screen.c) pero despues tendria que hacer un loader o algo dinmaico
void load_field_screen_gui_entities(){
    SDL_Texture *big_atlas = get_texture_by_index(0);
    SDL_Rect nube_rect = {10, 10, 100, 50};
    append_new_entity(nube_rect, big_atlas, 101, 1, 0x00);
    
    SDL_Rect vaca_rect = {100, 10, 50, 50};
    append_new_entity(vaca_rect, big_atlas, 102, 0, 0x00); 
    append_new_entity(vaca_rect, big_atlas, 103, 0, 0x00);

    SDL_Rect grass_rect = {10, 10, 100, 50};
    append_new_entity(nube_rect, big_atlas, 101, 1, 0x00);
    return;
}
