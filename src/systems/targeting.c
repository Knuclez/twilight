#include <stdlib.h>
#include "systems/targeting.h"
#include "ecs/target_ecs.h"
#include "ecs/is_cow_food_ecs.h"

//should be here because shouldnt call directly
#include "scenes/field_scene.h"

void scan_for_food(int cow_id, Position *cow_pos){
    int food_amt = get_cow_food_comp_amount();
    int* food_ents = get_cow_food_entities();
    for(int i = 0; i < food_amt ; i++){
	int food_id = *(food_ents + i);
	if (food_id == -1){
	    continue;
	}
	Position *food_pos = get_id_associated_position(food_id);
	if (abs(food_pos->x - cow_pos->x) < 120){
	   add_target_component_to_id(cow_id, food_id); 
	}
    }
}

void drop_target(int tgt_id){
    int tgt_amt = get_target_component_amount();
    int *tgt_ents = get_targets_list(); 
    for(int i = 0; i < tgt_amt; i++){
	int* p_ent = tgt_ents + i;
	if(*p_ent == tgt_id){
	    *p_ent = -1;
	}
    }
}

void remove_target_entity(int tgt_id){
    drop_target(tgt_id);
    remove_field_entity(tgt_id);
}
