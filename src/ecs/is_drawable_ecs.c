#include <string.h>
#include <stdio.h>
#include "ecs/ec_hash_list.h"
#include "ecs/is_drawable_ecs.h"
#include "ecs/position_ecs.h"

int drawables[MAX_ENTITIES];
int drawCompAmount;

int get_drawable_comp_amount(){
    return drawCompAmount;
}

void add_is_drawable_component_to_id(int id){
    Position *pos = get_id_associated_position(id);
    if (pos == NULL){
	printf("Cannot make drawable entity:%u ,no pos component \n", id);
    }
    drawables[drawCompAmount] = id;
    drawCompAmount += 1;
    return;
}


void init_is_drawable_ecs(){
    memset(drawables, 0xCC, sizeof(int) * MAX_ENTITIES);
    return;
}
