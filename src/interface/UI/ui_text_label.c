#include <stdio.h>
#include <string.h>
#include "interface/UI/ui_text_label.h"
#include "interface/rendering/texturing.h"

void ui_text_label_list_init(UITextLabelList *list){
    memset(list, 0, sizeof(UITextLabelList));
}

void ui_text_label_add(UITextLabelList *list, SDL_Rect rect, const char *label){
    if (list->count >= MAX_UI_TEXT_LABELS){
        printf("[ui] MAX_UI_TEXT_LABELS alcanzado\n");
        return;
    }
    UITextLabel *b    = &list->labels[list->count++];
    b->rect           = rect;
    b->label          = label;
    b->active         = 1;
}

void ui_text_label_render(UITextLabelList *list, SDL_Renderer *renderer){
    for (int i = 0; i < list->count; i++){
        UITextLabel *b = &list->labels[i];
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
