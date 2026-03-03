#include <stdio.h>
#include <string.h>
#include "interface/UI/ui_button.h"
#include "interface/rendering/texturing.h"

void ui_button_list_init(UIButtonList *list){
    memset(list, 0, sizeof(UIButtonList));
}

void ui_button_add(UIButtonList *list, SDL_Rect rect, const char *label, void (*on_click)(void)){
    if (list->count >= MAX_UI_BUTTONS){
        printf("[ui] MAX_UI_BUTTONS alcanzado\n");
        return;
    }
    UIButton *b       = &list->buttons[list->count++];
    b->rect           = rect;
    b->label          = label;
    b->on_click       = on_click;
    b->on_click_data  = NULL;
    b->user_data      = 0;
    b->active         = 1;
}

void ui_button_add_with_data(UIButtonList *list, SDL_Rect rect, const char *label, int user_data, void (*on_click_data)(int)){
    if (list->count >= MAX_UI_BUTTONS){
        printf("[ui] MAX_UI_BUTTONS alcanzado\n");
        return;
    }
    UIButton *b       = &list->buttons[list->count++];
    b->rect           = rect;
    b->label          = label;
    b->on_click       = NULL;
    b->on_click_data  = on_click_data;
    b->user_data      = user_data;
    b->active         = 1;
}

void ui_button_handle_click(UIButtonList *list, int mouse_x, int mouse_y){
    SDL_Point p = { mouse_x, mouse_y };
    for (int i = 0; i < list->count; i++){
        UIButton *b = &list->buttons[i];
        if (!b->active) continue;
        if (SDL_PointInRect(&p, &b->rect)){
            if (b->on_click)      b->on_click();
            if (b->on_click_data) b->on_click_data(b->user_data);
            break;
        }
    }
}

void ui_button_render(UIButtonList *list, SDL_Renderer *renderer){
    for (int i = 0; i < list->count; i++){
        UIButton *b = &list->buttons[i];
        if (!b->active) continue;

        /* fondo */
        SDL_SetRenderDrawColor(renderer, 60, 60, 60, 220);
        SDL_RenderFillRect(renderer, &b->rect);

        /* borde */
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderDrawRect(renderer, &b->rect);

        /* texto */
        if (b->label){
            SDL_Texture *txt = instance_dynamic_text_texture(renderer, (char*)b->label);
            if (txt){
                int tw, th;
                SDL_QueryTexture(txt, NULL, NULL, &tw, &th);
                /* centrar verticalmente, margen izquierdo de 4px */
                SDL_Rect dst = {
                    b->rect.x + 4,
                    b->rect.y + (b->rect.h - th) / 2,
                    tw,
                    th
                };
                /* recortar si el texto es mas ancho que el boton */
                if (dst.w > b->rect.w - 8) dst.w = b->rect.w - 8;
                SDL_RenderCopy(renderer, txt, NULL, &dst);
            }
        }
    }
}
