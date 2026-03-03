#ifndef UI_BUTTON_H
#define UI_BUTTON_H

#include <SDL2/SDL.h>

#define MAX_UI_BUTTONS 32

typedef struct {
    SDL_Rect    rect;
    void        (*on_click)(void);        /* boton sin datos */
    void        (*on_click_data)(int);    /* boton con dato entero (ej: entity index) */
    int         user_data;               /* dato que se pasa a on_click_data */
    const char  *label;
    int         active;
} UIButton;

typedef struct {
    UIButton buttons[MAX_UI_BUTTONS];
    int      count;
} UIButtonList;

void ui_button_list_init      (UIButtonList *list);
void ui_button_add            (UIButtonList *list, SDL_Rect rect, const char *label, void (*on_click)(void));
void ui_button_add_with_data  (UIButtonList *list, SDL_Rect rect, const char *label, int user_data, void (*on_click_data)(int));
void ui_button_handle_click   (UIButtonList *list, int mouse_x, int mouse_y);
void ui_button_render         (UIButtonList *list, SDL_Renderer *renderer);

#endif
