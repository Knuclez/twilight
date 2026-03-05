#include <stdio.h>
#include <SDL2/SDL.h>

#include "editor/editor_main.h"
#include "editor/editor_rendering.h"
#include "entities.h"
#include "game_state.h"
#include "interface/rendering/texturing.h"
#include "interface/UI/ui_button.h"

/* Declarada en editor_main.c (no-static) */
void btn_entity_selected(int index);

/* ── sub-renderers ─────────────────────────────────────────────────── */

static void render_border(SDL_Renderer *renderer, int w, int h){
    int border = 4;
    SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
    SDL_Rect top    = {0,        0,        w,      border};
    SDL_Rect bottom = {0,        h-border, w,      border};
    SDL_Rect left   = {0,        0,        border, h     };
    SDL_Rect right  = {w-border, 0,        border, h     };
    SDL_RenderFillRect(renderer, &top);
    SDL_RenderFillRect(renderer, &bottom);
    SDL_RenderFillRect(renderer, &left);
    SDL_RenderFillRect(renderer, &right);
}

static void render_fps(SDL_Renderer *renderer){
    static Uint32 last_ticks = 0;
    Uint32 now  = SDL_GetTicks();
    Uint32 diff = now - last_ticks;
    float  fps  = diff > 0 ? 1000.0f / (float)diff : 0.0f;
    last_ticks  = now;

    char fps_buf[32];
    snprintf(fps_buf, sizeof(fps_buf), "FPS: %.0f", fps);

    SDL_Texture *fps_tex = instance_dynamic_text_texture(renderer, fps_buf);
    if (fps_tex){
        int tw, th;
        SDL_QueryTexture(fps_tex, NULL, NULL, &tw, &th);
        SDL_Rect dst = {100, 10, tw, th};
        SDL_RenderCopy(renderer, fps_tex, NULL, &dst);
        SDL_DestroyTexture(fps_tex);
    }
}

static void render_entity_panel(SDL_Renderer *renderer, int panel_x, int panel_w, int h){
    EditorState *es      = get_editor();
    GameState   *gs      = get_game_state_p();
    Entity      *entities = gs->entities;
    int          max_ents = gs->max_index;

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 40, 40, 40, 178);
    SDL_Rect panel_bg = {panel_x, 0, panel_w, h};
    SDL_RenderFillRect(renderer, &panel_bg);

    int row_h  = 24;
    int margin = 4;
    ui_button_list_init(&es->entity_buttons);

    int row = 0;
    for (int i = 0; i < max_ents; i++){
        if (entities[i].key.index == 0) continue;
        static char labels[MAX_ENTITIES][32];
        snprintf(labels[i], sizeof(labels[i]), "[%d] ent", entities[i].key.index);
        SDL_Rect r = {panel_x + margin, margin + row * (row_h + margin), panel_w - margin * 2, row_h};
        ui_button_add_with_data(&es->entity_buttons, r, labels[i], entities[i].key.index, btn_entity_selected);
        row++;
    }
    ui_button_render(&es->entity_buttons, renderer);
}

static void render_inspector(SDL_Renderer *renderer, int w, int h){
    EditorState *es       = get_editor();
    GameState   *gs       = get_game_state_p();
    Entity      *entities = gs->entities;

    if (!(es->editor_bitmask & IS_INSPECTING_ENTITY)) return;

    Entity inspected_ent = entities[es->inspected_entity.index];
    if (inspected_ent.key.index == 0) return;
    if (inspected_ent.key.generation != es->inspected_entity.generation) return;

    printf("x is %u\n", inspected_ent.position.x);

    int inspector_w = w / 4;
    int inspector_x = w - inspector_w;
    SDL_SetRenderDrawColor(renderer, 40, 40, 40, 50);
    SDL_Rect inspector_rect = {inspector_x, 50, inspector_w, h / 2};
    SDL_RenderFillRect(renderer, &inspector_rect);
}

/* ── entry point ───────────────────────────────────────────────────── */

void editor_render(SDL_Renderer *renderer){
    EditorState *es = get_editor();
    int w, h;
    SDL_GetRendererOutputSize(renderer, &w, &h);

    int panel_w = w / 4;
    int panel_x = w - panel_w;

    render_border(renderer, w, h);
    render_fps(renderer);
    ui_button_render(&es->buttons, renderer);   /* botones fijos (Pause, Save) */
    render_entity_panel(renderer, panel_x, panel_w, h);
    render_inspector(renderer, w, h);
}
