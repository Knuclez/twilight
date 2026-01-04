#ifndef IS_COW_FOOD_H
#define IS_COW_FOOD_H

int get_cow_food_comp_amount();
int* get_cow_food_entities();
int is_id_cow_food(int id);
void add_is_cow_food_component_to_id(int id);
void init_is_cow_food_ecs();
void remove_is_cow_food_from_id(int id);
#endif
