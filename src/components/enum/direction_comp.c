#include <stdio.h>
#include "storage_structures/ec_hash_list.h"
#include "components/direction_comp.h"

ECBucket dirIdList[LIST_SIZE];
Direction directions[MAX_ENTITIES];
int dirCompAmount;

int direction_register(){
   Direction new = IDLE; 
   directions[dirCompAmount] = new;
   dirCompAmount ++;
   return dirCompAmount - 1;
}

//PUBLICS
Direction* directions_get(){
    return directions;
}

Direction direction_get_by_key(EntityKey key){
    int indx = component_index_get(dirIdList, key);
    return directions[indx];
}

int direction_index_get_from_key(EntityKey key){
    int indx = component_index_get(dirIdList, key);
    return indx;
}

void direction_component_add(EntityKey key){
    int index = direction_register();
    ec_register(dirIdList, key, index);
}


void direction_component_remove(EntityKey key){
    ec_value_change(dirIdList, key, -1);
}

int direction_component_list_init(){
    dirCompAmount = 0;
    return ec_hash_list_init(dirIdList);
}
