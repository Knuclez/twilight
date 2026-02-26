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

static int direction_to_row(Direction dir) {
    switch(dir) {
        case DIR_NW: return 0;
        case DIR_N:  return 1;
        case DIR_NE: return 2;
        case DIR_W:  return 3;
        case DIR_E:  return 4;
        case DIR_SW: return 5;
        case DIR_S:  return 6;
        case DIR_SE: return 7;
        default:     return 0;
    }
}

void draw_entities(SDL_Renderer *r, float delta){
    SDL_Texture *txt;
    Entity *ents = entities_get();
    int max = entities_max_index();
    AnimationClip *clips = animation_clips_get();
    AnimationSet  *sets  = animation_sets_get();
    (void)sets;

    for (int i = 0; i < max; i++) {
        Entity *e = &ents[i];
        if (e->key.index < 0) continue;
        if (!(e->bitmask & IS_DRAWABLE_MASK)) continue;

        PhysicalBounds pb = e->physical_bounds;
        int draw_x = e->position.x - e->size.x;
        int draw_y = e->position.y - e->size.y;
        int draw_width = e->size.x * 2;
        int draw_height = e->size.y * 2;
        SDL_Rect output_rect = {draw_x, draw_y, draw_width, draw_height};

        SDL_Rect src_rect;
        if (e->bitmask & HAS_ANIMATION_MASK) {
            int clip_idx = animation_get_clip_for_entity(e->animation.anim_set_index,
                                                         e->combat_state, e->direction);
            AnimationClip clip = clips[clip_idx];
            txt = get_texture_by_index(clip.txtr_indx);
            if (!txt) continue;
            int src_x = clip.origin_x + (e->animation.current_frame * clip.x_stride);
            int src_y = clip.origin_y + (direction_to_row(e->direction) * clip.y_stride);
            src_rect = (SDL_Rect){ src_x, src_y, clip.frame_w, clip.frame_h };
        } else {
            SpriteSource sprite_src = e->sprite_source;
            txt = get_texture_by_index(sprite_src.txtr_indx);
            if (!txt) continue;
            src_rect = (SDL_Rect){ sprite_src.x, sprite_src.y,
                                   sprite_src.width, sprite_src.height };
        }

        SDL_RenderCopy(r, txt, &src_rect, &output_rect);
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
