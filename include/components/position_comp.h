#ifndef POSITION_COMP_H
#define POSITION_COMP_H

typedef struct {
    int x;
    int y;
}Position;

Position* positions_get();
int position_index_get_from_key();
void position_component_add();
void position_component_remove();
int position_component_list_init();
#endif
