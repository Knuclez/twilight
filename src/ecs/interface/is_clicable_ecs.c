#include <string.h>
#include <stdio.h>
#include "ecs/ec_hash_list.h"
#include "ecs/is_clickable_ecs.h"
#include "ecs/position_ecs.h"

int clickables[MAX_ENTITIES];
int clickCompAmount;

int get_clickable_comp_amount(){
    return clickCompAmount;
}

int* get_clickable_entities(){
    return clickables;
}

void add_is_clickable_component_to_id(int id){
    clickables[clickCompAmount] = id;
    clickCompAmount += 1;
    return;
}


void init_is_clickable_ecs(){
    memset(clickables, 0xCC, sizeof(int) * MAX_ENTITIES);
    return;
}
