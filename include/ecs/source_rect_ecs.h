#ifndef SOURCE_RECT_H
#define SOURCE_RECT_H

typedef struct {
    int x;
    int y;
    int w;
    int h;
} SourceRect;

int get_source_rect_comp_amount();
SourceRect* get_id_associated_source_rect(int id);
int register_source_rect(int n_x, int n_y, int n_w, int n_h);
void add_source_rect_component_to_id(int id, int x, int y, int w, int h);
void remove_source_rect_from_id(int id);
void init_source_rect_ecs();

#endif
