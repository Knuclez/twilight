#ifndef UI_INPUT_FIELD_H
#define UI_INPUT_FIELD_H

#include <SDL2/SDL.h>

#define MAX_INPUT_FIELD_LEN  128
#define MAX_UI_INPUT_FIELDS  16

typedef struct {
    SDL_Rect    rect;
    char        buffer[MAX_INPUT_FIELD_LEN];
    void        (*on_submit)(const char *text);
    int         active;
    int         focused;
} UIInputField;

typedef struct {
    UIInputField fields[MAX_UI_INPUT_FIELDS];
    int          count;
} UIInputFieldList;

/* Coordinates of the currently focused input field (set on focus). */
extern int g_input_field_x;
extern int g_input_field_y;

void ui_input_field_list_init   (UIInputFieldList *list);
void ui_input_field_add         (UIInputFieldList *list, SDL_Rect rect, void (*on_submit)(const char *text));
void ui_input_field_handle_click(UIInputFieldList *list, int mouse_x, int mouse_y);
void ui_input_field_handle_text (UIInputFieldList *list, const char *text);
void ui_input_field_handle_key  (UIInputFieldList *list, SDL_Keycode key);
void ui_input_field_render      (UIInputFieldList *list, SDL_Renderer *renderer);

#endif
