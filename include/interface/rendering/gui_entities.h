#ifndef G_ENTITYS_H
#define G_ENTITYS_H

#include <SDL2/SDL.h>

typedef struct {
    int id;
    SDL_Rect rect;
    SDL_Texture *txt;
    int z;
    unsigned char flags;
} GUI_Entity;

typedef struct {
    GUI_Entity **list;
    int size;
    int amount;
} ComponentList;

void alloc_gui_entities_space();
void unload_scene_gui_entities();
void append_new_entity(SDL_Rect rect,SDL_Texture *txt, int id, int z, unsigned char flags);
GUI_Entity* get_entity_by_id(int id);
ComponentList* get_click_entities();
#endif
