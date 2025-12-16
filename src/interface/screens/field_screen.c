#include <SDL2/SDL.h>
#include <stdio.h>

#include "interface/rendering/texturing.h"
#include "interface/screens/field_screen.h"
#include "interface/rendering/render_auxs.h"
#include "interface/rendering/gui_entities.h"


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
    SDL_RenderCopy(r, nub->txt, NULL, &rect);
}

void draw_cow(SDL_Renderer *r){
    GUI_Entity *ent = get_entity_by_id(102);
    SDL_Rect rect = ent->rect;
    SDL_RenderCopy(r, ent->txt, NULL, &rect);
}

void present_field_screen(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, 0, 210, 0, 255);
    SDL_RenderClear(renderer);

    draw_cow(renderer);
    draw_cloud(renderer);
    SDL_RenderPresent(renderer);
}

//void append_new_entity(SDL_Rect rect,SDL_Texture *txt, int id, int z, unsigned char flags)
void load_field_screen_gui_entities(){
    SDL_Rect nube_rect = {10, 10, 100, 50};
    SDL_Texture *nube_tx = get_texture_by_index(0);
    append_new_entity(nube_rect, nube_tx, 101, 1, 0x00);
    
    SDL_Rect vaca_rect = {100, 10, 50, 50};
    SDL_Texture *vaca_tx = get_texture_by_index(1);
    append_new_entity(vaca_rect, vaca_tx, 102, 0, 0x00);
    return;
}
