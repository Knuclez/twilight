#ifndef POSITION_ECS_H
#define POSITION_ECS_H

typedef struct {
    int x;
    int y;
} Position;

int init_position_ecs();
void add_position_component_to_id(int id, int x, int y);
int get_position_component_amount();
Position* get_id_associated_position(int id);
Position* get_position_by_index(int id);

#endif
