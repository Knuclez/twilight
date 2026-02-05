// src/interface/screens/field_screen.c
#include <stdio.h>

#include "interface/rendering/texturing.h"
#include "interface/rendering/render_auxs.h"
#include "interface/screen.h"
#include "interface/animations_rsc.h"

#include "scenes/field_scene.h"
#include "game_state.h"
#include "systems/movement.h"

#include "entities.h"
#include "components/animation_rsc_index.h"
#include "components/position_comp.h"
#include "components/size_comp.h"
#include "components/physical_bounds_comp.h"
#include "components/sprite_source_comp.h"
#include "components/direction_comp.h"
#include "components/entity_bitmasks.h"

void screen_entity_clicked(int id_ent){
    return;
}

void screen_text_event(SDL_Event event){
    return;
}

void draw_debug(SDL_Renderer *r, int x, int y, int width, int height){
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    int center_x = x + (width / 2);
    int center_y = y + (height / 2);

    SDL_Point contour[5];
    contour[0].x = x;
    contour[0].y = y;
    contour[1].x = x + width;
    contour[1].y = y;
    contour[2].x = x + width;
    contour[2].y = y + height;
    contour[3].x = x;
    contour[3].y = y + height;
    contour[4].x = x;
    contour[4].y = y;
    SDL_Rect rect = {center_x, center_y, 10, 10};
    SDL_RenderFillRect(r, &rect);
    SDL_RenderDrawLines(r, contour, 5);
    return;
}

void draw_debug_red(SDL_Renderer *r, int x, int y, int width, int height){
    SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
    int center_x = x + (width / 2);
    int center_y = y + (height / 2);

    SDL_Point contour[5];
    contour[0].x = x;
    contour[0].y = y;
    contour[1].x = x + width;
    contour[1].y = y;
    contour[2].x = x + width;
    contour[2].y = y + height;
    contour[3].x = x;
    contour[3].y = y + height;
    contour[4].x = x;
    contour[4].y = y;
    SDL_Rect rect = {center_x, center_y, 10, 10};
    SDL_RenderFillRect(r, &rect);
    SDL_RenderDrawLines(r, contour, 5);
    return;
}

void draw_entities(SDL_Renderer *r, float delta){
    Position *positions = positions_get();
    SpriteSource *sprite_sources = sprite_sources_get();
    int pos_count = position_count_get();
    AnimationRsc *animation_rscs = animation_rscs_get();
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

        // ⭐ Obtener sprite_source del nuevo componente
        EntityKey key = position_get_entity_by_index(pos_idx);
        int sprite_src_idx = sprite_source_index_get_from_key(key);
        SpriteSource sprite_src = sprite_sources[sprite_src_idx];

        txt = get_texture_by_index(sprite_src.txtr_indx);
        if (txt == NULL) {
            continue;
        }

        // Aplicar offset de animación si tiene
        int sprite_shift_x = 0;
        int sprite_shift_y = 0;
            if (bitmask & HAS_ANIMATION_MASK) {
    	    int anim_comp_idx = animation_resource_index_get_from_key(key);
                int anim_rsc_i = animation_resource_get_rsc_index_from_key(key);
                if (anim_rsc_i >= 0) {
                    anim_data = animation_rscs[anim_rsc_i];

                    // ⭐ Obtener frame actual y calcular X del sprite
                    int current_frame = animation_state_get_frame(key);
                    sprite_src.x = anim_data.idle_x + 8 + ((current_frame + 1) * anim_data.x_offset);

                    // Obtener dirección para calcular offset Y
                    Direction *directions = directions_get();
                    int dir_idx = direction_index_get_from_key(key);
                    if (dir_idx >= 0) {
                        Direction dir = directions[dir_idx];
                        if (dir == 0){
                            sprite_src.x = anim_data.idle_x;
                        } else {
                            sprite_shift_y = anim_data.y_offset * (dir - 1);
                        }
                    }
                }
    	    animation_state_update(key, delta, 10);

        }

        // ⭐ Acceso directo a posición del mundo
        Position position = positions[pos_idx];
	Size size = size_get_by_key(key);
	PhysicalBounds pb= physical_bounds_get_by_key(key);
        
        SDL_Rect output_rect = {position.x, position.y, size.x, size.y};
        SDL_Rect src_rect = {sprite_src.x, sprite_src.y + sprite_shift_y, sprite_src.width, sprite_src.height};
        SDL_RenderCopy(r, txt, &src_rect, &output_rect);
	draw_debug(r, position.x, position.y, size.x, size.y);
	draw_debug_red(r,position.x + pb.x,position.y + pb.y,pb.width,pb.height);
    }
}

void screen_present(SDL_Renderer *renderer, float delta){
    SDL_SetRenderDrawColor(renderer, 0, 210, 0, 255);
    SDL_RenderClear(renderer);

    draw_entities(renderer, delta);
    SDL_RenderPresent(renderer);
}

void screen_init(){
    return;
}
