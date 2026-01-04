#ifndef IS_DRAWABLE_ECS
#define IS_DRAWABLE_ECS

void init_is_drawable_ecs();
void add_is_drawable_component_to_id(int id);
int get_drawable_comp_amount();
int* get_drawables();
void remove_is_drawable_from_id(int id);
#endif
