// src/interface/screens/field_screen.c
#include <SDL2/SDL.h>
#include <stdio.h>

#include "interface/rendering/texturing.h"
#include "interface/screens/field_screen.h"
#include "interface/rendering/render_auxs.h"
#include "interface/animations_rsc.h"
#include "scenes/field_scene.h"
#include "game_state.h"
#include "systems/movement.h"

#include "components/animation_rsc_index.h"
#include "components/position_comp.h"
#include "components/sprite_source_comp.h"
#include "components/texture_indx_comp.h"
#include "components/direction_comp.h"
#include "components/entity_bitmasks.h"
#include "entities.h"

void field_screen_entity_clicked(int id_ent, SDL_Event event){
    return;
}

void field_screen_key_event(SDL_Event event){
    EntityKey player = (get_game_state_p())->player_key;
    Direction *ds = directions_get();
    int dir_indx = direction_index_get_from_key(player);
    switch(event.key.keysym.sym){
    case SDLK_d:
        ds[dir_indx] = E;
        break;
    case SDLK_a:
        ds[dir_indx] = W;
        break;
    }
    return;
}

void field_screen_key_up_event(SDL_Event event){
    EntityKey player = (get_game_state_p())->player_key;
    Direction *ds = directions_get();
    int dir_indx = direction_index_get_from_key(player);
    ds[dir_indx] = IDLE; 
    return;
}

void field_screen_input_event(SDL_Event event){
    return;
}

void draw_entities(SDL_Renderer *r){
    Position *positions = positions_get();
    SpriteSource *sprite_sources = sprite_sources_get();
    int pos_count = position_count_get();
    int *ent_bitmasks = entity_bitmasks;

    AnimationRsc anim_data;
    SDL_Texture *txt;
    
    // ⭐ ITERACION EFICIENTE: Solo sobre entidades con posición
    for (int pos_idx = 0; pos_idx < pos_count; pos_idx++) {
        
        // Obtener índice de entidad desde la posición
        int entity_idx = position_to_entity_index_get(pos_idx);
        if (entity_idx < 0) {
            continue;
        }
        
        // ⭐ Acceso O(1) al bitmask desde array global
        int bitmask = ent_bitmasks[entity_idx];

        if (!(bitmask & IS_DRAWABLE_MASK)) {
            continue;
        }

        // Obtener textura - necesitamos EntityKey para esto
        EntityKey key = position_get_entity_by_index(pos_idx);
        int txt_idx = texture_get_index_by_key(key);
        txt = get_texture_by_index(txt_idx);
        
        if (txt == NULL) {
            continue;
        }

        // ⭐ Obtener sprite_source del nuevo componente
        int sprite_src_idx = sprite_source_index_get_from_key(key);
        if (sprite_src_idx < 0) {
            continue;
        }
        
        SpriteSource sprite_src = sprite_sources[sprite_src_idx];

        // Aplicar offset de animación si tiene
        int sprite_shift = 0;
        if (bitmask & HAS_ANIMATION_MASK) {
            anim_data = rapp_animation_rsc_get();
            // Obtener dirección para calcular offset
            Direction *directions = directions_get();
            int dir_idx = direction_index_get_from_key(key);
            if (dir_idx >= 0) {
                Direction dir = directions[dir_idx];
                sprite_shift = anim_data.x_offset * dir;
            }
        }

        // ⭐ Acceso directo a posición del mundo
        Position position = positions[pos_idx];
        
        SDL_Rect output_rect = {position.x, position.y, 130, 160};
        SDL_Rect src_rect = {sprite_src.x + sprite_shift, sprite_src.y, sprite_src.width, sprite_src.height};
        SDL_RenderCopy(r, txt, &src_rect, &output_rect);
    }
}

void present_field_screen(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, 0, 210, 0, 255);
    SDL_RenderClear(renderer);

    draw_entities(renderer);
    SDL_RenderPresent(renderer);
}

void init_field_screen(){
    return;
}