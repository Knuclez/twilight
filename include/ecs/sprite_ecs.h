#ifndef SPRITE_ECS_H 
#define SPRITE_ECS_H 

typedef struct {
    int w;
    int h;
    int x;
    int y;
} SpriteRect;

int init_spr_rect_ecs();
void add_spr_rect_component_to_id(int id,int w, int h, int x, int y);
int get_spr_rect_component_amount();
SpriteRect* get_id_associated_spr_rect(int id);
SpriteRect* get_spr_rect_by_index(int id);

#endif
