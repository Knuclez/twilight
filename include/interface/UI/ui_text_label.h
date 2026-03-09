#ifndef UI_TEXT_LABEL_H 
#define UI_TEXT_LABEL_H

#include <SDL2/SDL.h>

#define MAX_UI_TEXT_LABELS 32

typedef struct {
    SDL_Rect    rect;
    const char  *label;
    int         active;
} UITextLabel;

typedef struct {
    UITextLabel labels[MAX_UI_TEXT_LABELS];
    int      count;
} UITextLabelList;

void ui_text_label_list_init      (UITextLabelList *list);
void ui_text_label_add            (UITextLabelList *list, SDL_Rect rect, const char *label);
void ui_text_label_render         (UITextLabelList *list, SDL_Renderer *renderer);

#endif
