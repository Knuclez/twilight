#include <stdio.h>
#include "storage_structures/ec_hash_list.h"
#include "components/position_comp.h"

ECBucket posIdList[LIST_SIZE];
Position positions[MAX_ENTITIES];
int posCompAmount;

int position_register(int n_x, int n_y){
   Position new; 
   new.x = n_x;
   new.y = n_y;
   positions[posCompAmount] = new;
   posCompAmount ++;
   return posCompAmount - 1;
}

//PUBLICS
Position* positions_get(){
    return positions;
}

int position_index_get_from_key(EntityKey key){
    int pos_indx = component_index_get(posIdList, key);
    return pos_indx;
}

void position_component_add(EntityKey key, int x, int y){
    int index = position_register(x, y);
    ec_register(posIdList, key, index);
}


void position_component_remove(EntityKey key){
    ec_value_change(posIdList, key, -1);
}

int position_component_list_init(){
    posCompAmount = 0;
    return ec_hash_list_init(posIdList);
}
