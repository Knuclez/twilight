#ifndef DIRECTION_COMP_H
#define DIRECTION_COMP_H

typedef enum {IDLE, NW, N, NE, W, E, SW, S, SE} Direction;

Direction* directions_get();
Direction direction_get_by_key();
int direction_index_get_from_key();
void direction_component_add();
void direction_component_remove();
int direction_component_list_init();
#endif
