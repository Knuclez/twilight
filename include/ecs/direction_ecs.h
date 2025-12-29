#ifndef DIRECTION_ECS_H 
#define	DIRECTION_ECS_H 

typedef enum{DOWN, UP, RIGHT, LEFT} Direction;

int init_direction_ecs();
void add_direction_component_to_id(int id);
int get_direction_component_amount();
Direction* get_id_associated_direction(int id);
Direction* get_direction_by_index(int id);

#endif
