// src/interface/screens/field_screen.c
#include <stdio.h>

#include "interface/rendering/texturing.h"
#include "interface/rendering/render_auxs.h"
#include "interface/screen.h"
#include "interface/animations_rsc.h"

#include "scenes/field_scene.h"
#include "game_state.h"
#include "systems/movement.h"

#include "entities.h"  /* unified entity storage */

void screen_entity_clicked(int id_ent){
    (void)id_ent;
}

void screen_text_event(SDL_Event event){
    (void)event;
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
}

void draw_debug_red(SDL_Renderer *r, int x, int y, int width, int height){
    SDL_SetRenderDrawColor(r, 255, 0, 120, 120);
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
}

void draw_entities(SDL_Renderer *r, float delta){
    SDL_Texture *txt;
    Entity *ents = entities_get();
    int max = entities_max_index();

    /* get animation resources for sprite positioning */
    AnimationRsc* anim_rscs = animation_rscs_get();

    for (int i = 0; i < max; i++) {
        Entity *e = &ents[i];
        if (e->key.index < 0) continue;
        if (!(e->bitmask & IS_DRAWABLE_MASK)) continue;

        SpriteSource sprite_src = e->sprite_source;
        txt = get_texture_by_index(sprite_src.txtr_indx);
        if (!txt) continue;

        int sprite_shift_y = 0;
        if (e->bitmask & HAS_ANIMATION_MASK) {
            int anim_idx = e->animation.resource_index;
            if (anim_idx >= 0 && anim_idx < 10) {
                AnimationRsc anim_data = anim_rscs[anim_idx];
                int current_frame = e->animation.current_frame;

		if (e->direction == IDLE) {
                    sprite_src.x = anim_data.idle_x;
                } else {
		    sprite_src.x = anim_data.idle_x + 8 + ((current_frame + 1) * anim_data.x_offset);
                    //sprite_src.x = anim_data.idle_x + (current_frame * anim_data.x_offset);
                    /* direction-based Y offset */
                    sprite_shift_y = anim_data.y_offset * (e->direction - 1);
                }    
		            
	    }
        }


	PhysicalBounds pb = e->physical_bounds;

        int draw_x = e->position.x - e->size.x;
        int draw_y = e->position.y - e->size.y;
        int draw_width = e->size.x * 2;
        int draw_height = e->size.y * 2;
        SDL_Rect output_rect = {draw_x, draw_y, draw_width, draw_height};
        SDL_Rect src_rect = {sprite_src.x, sprite_src.y + sprite_shift_y,
                             sprite_src.width, sprite_src.height};
        SDL_RenderCopy(r, txt, &src_rect, &output_rect);
        //draw_debug(r, draw_x, draw_y, draw_width, draw_height);
	draw_debug_red(r, draw_x + pb.x, draw_y + pb.y, pb.width * 2, pb.height * 2);
	if (e->combat_state == TREMBLE){
	    SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
	    SDL_Rect hit_mark_rect = { draw_x, draw_y, 10, 10};
	    SDL_RenderFillRect(r, &hit_mark_rect);
	}
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
