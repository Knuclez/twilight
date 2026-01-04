#include <string.h>
#include <stdio.h>
#include "ecs/ec_hash_list.h"
#include "ecs/is_drawable_ecs.h"
#include "ecs/position_ecs.h"

ECBucket isDrawableIdList[LIST_SIZE];
int drawables[MAX_ENTITIES];
int drawCompAmount;

int get_drawable_comp_amount(){
    return drawCompAmount;
}

int* get_drawables(){
    return drawables;
}


void add_is_drawable_component_to_id(int id){
    Position *pos = get_id_associated_position(id);
    if (pos == NULL){
	printf("Cannot make drawable entity:%u ,no pos component \n", id);
    }
    drawables[drawCompAmount] = id;
    register_ec(isDrawableIdList, id, drawCompAmount);
    drawCompAmount += 1;
    return;
}


void remove_is_drawable_from_id(int id){
    int indx = get_component_index_by_id(isDrawableIdList, id);
    drawables[indx] = -1;
    change_ec(isDrawableIdList, id, -1);
}

void init_is_drawable_ecs(){
     init_ec_hash_list(isDrawableIdList);
    return;
}
