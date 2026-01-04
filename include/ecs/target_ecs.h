#ifndef TARGET_ECS_H 
#define	TARGET_ECS_H 

int init_target_ecs();
void add_target_component_to_id(int id, int tgt_id);
int get_target_component_amount();
int* get_targets_list();
int get_id_associated_target(int id);
int get_target_by_index(int id);

#endif
