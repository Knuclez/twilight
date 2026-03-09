#include <stdio.h>
#include <string.h>
#include "interface/UI/ui_input_field.h"
#include "interface/rendering/texturing.h"
#include "editor/editor_main.h"

/* Global position of the currently focused input field. */
int g_input_field_x = 0;
int g_input_field_y = 0;

void ui_input_field_list_init(UIInputFieldList *list){
    memset(list, 0, sizeof(UIInputFieldList));
}

void ui_input_field_add(UIInputFieldList *list, SDL_Rect rect, void (*on_submit)(const char *text)){
    if (list->count >= MAX_UI_INPUT_FIELDS){
        printf("[ui] MAX_UI_INPUT_FIELDS alcanzado\n");
        return;
    }
    UIInputField *f  = &list->fields[list->count++];
    f->rect          = rect;
    f->on_submit     = on_submit;
    f->active        = 1;
    f->focused       = 0;
    f->buffer[0]     = '\0';
}

/* Defocus every field in this list and stop text input. */
static void defocus_all(UIInputFieldList *list){
    for (int i = 0; i < list->count; i++)
        list->fields[i].focused = 0;
    get_editor()->editor_bitmask &= ~IS_READING_INPUT;
    SDL_StopTextInput();
}

void ui_input_field_handle_click(UIInputFieldList *list, int mouse_x, int mouse_y){
    SDL_Point p = { mouse_x, mouse_y };
    int hit = 0;
    for (int i = 0; i < list->count; i++){
        UIInputField *f = &list->fields[i];
        if (!f->active) continue;
        if (SDL_PointInRect(&p, &f->rect)){
            defocus_all(list);
            f->focused = 1;
            /* Store global coordinates for external consumers. */
            g_input_field_x = f->rect.x;
            g_input_field_y = f->rect.y;
            get_editor()->editor_bitmask |= IS_READING_INPUT;
            SDL_StartTextInput();
            hit = 1;
            break;
        }
    }
    /* Click outside every field: defocus. */
    if (!hit) defocus_all(list);
}

void ui_input_field_handle_text(UIInputFieldList *list, const char *text){
    for (int i = 0; i < list->count; i++){
        UIInputField *f = &list->fields[i];
        if (!f->focused) continue;
        size_t cur = strlen(f->buffer);
        size_t inc = strlen(text);
        if (cur + inc < MAX_INPUT_FIELD_LEN - 1)
            strcat(f->buffer, text);
        break;
    }
}

void ui_input_field_handle_key(UIInputFieldList *list, SDL_Keycode key){
    for (int i = 0; i < list->count; i++){
        UIInputField *f = &list->fields[i];
        if (!f->focused) continue;

        if (key == SDLK_BACKSPACE){
            size_t len = strlen(f->buffer);
            if (len > 0) f->buffer[len - 1] = '\0';
        } else if (key == SDLK_RETURN || key == SDLK_RETURN2){
            if (f->on_submit) f->on_submit(f->buffer);
            f->buffer[0] = '\0';
            defocus_all(list);
        } else if (key == SDLK_ESCAPE){
            f->buffer[0] = '\0';
            defocus_all(list);
        }
        break;
    }
}

void ui_input_field_render(UIInputFieldList *list, SDL_Renderer *renderer){
    for (int i = 0; i < list->count; i++){
        UIInputField *f = &list->fields[i];
        if (!f->active) continue;

        /* fondo */
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 220);
        SDL_RenderFillRect(renderer, &f->rect);

        /* borde: blanco cuando enfocado, gris cuando no */
        if (f->focused)
            SDL_SetRenderDrawColor(renderer, 255, 220, 80, 255);
        else
            SDL_SetRenderDrawColor(renderer, 160, 160, 160, 255);
        SDL_RenderDrawRect(renderer, &f->rect);

        /* texto en tiempo real desde el buffer */
        const char *display = (strlen(f->buffer) > 0) ? f->buffer : "";
        if (display[0] != '\0'){
            SDL_Texture *txt = instance_dynamic_text_texture(renderer, (char*)display);
            if (txt){
                int tw, th;
                SDL_QueryTexture(txt, NULL, NULL, &tw, &th);
                SDL_Rect dst = {
                    f->rect.x + 4,
                    f->rect.y + (f->rect.h - th) / 2,
                    tw,
                    th
                };
                if (dst.w > f->rect.w - 8) dst.w = f->rect.w - 8;
                SDL_RenderCopy(renderer, txt, NULL, &dst);
            }
        }

        /* cursor parpadeante cuando enfocado */
        if (f->focused){
            int tw = 0;
            if (display[0] != '\0'){
                SDL_Texture *tmp = instance_dynamic_text_texture(renderer, (char*)display);
                if (tmp) SDL_QueryTexture(tmp, NULL, NULL, &tw, NULL);
            }
            int cx = f->rect.x + 4 + tw + 1;
            int cy = f->rect.y + 4;
            int ch = f->rect.h - 8;
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawLine(renderer, cx, cy, cx, cy + ch);
        }
    }
}
