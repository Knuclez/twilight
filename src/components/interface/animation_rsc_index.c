#include <stdio.h>
#include "storage_structures/ec_hash_list.h"
#include "components/animation_rsc_index.h"

/* esto se tiene q mover a la lista de animation resources
typedef struct{
    int sprite_x;
    int sprite_y;
    int x_offset;
    int frame_amount;
}AnimationData;

*/

ECBucket animRscIdList[LIST_SIZE];
int anim_rsc_indexes[MAX_ENTITIES];
int animRscCompAmount;

int animation_rsc_register(int resource_index){
   anim_rsc_indexes[animRscCompAmount] = resource_index;
   animRscCompAmount ++;
   return animRscCompAmount - 1;
}

//PUBLICS
int* animation_resource_indexes_get(){
    return anim_rsc_indexes;
}

int animation_resource_index_get_from_key(EntityKey key){
    int indx = component_index_get(animRscIdList, key);
    return indx;
}

void animation_resource_index_component_add(EntityKey key, int r_index){
    int iindex = animation_rsc_register(r_index);
    ec_register(animRscIdList, key, iindex);
}


void anim_rsc_component_remove(EntityKey key){
    ec_value_change(animRscIdList, key, -1);
}

int animation_rsc_index_component_list_init(){
    animRscCompAmount = 0;
    return ec_hash_list_init(animRscIdList);
}
