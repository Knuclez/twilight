#include <stdio.h>
#include "ecs/ec_hash_list.h"
#include "ecs/direction_ecs.h"


//EL DIA QUE TENGA MAS ENTITYS QUE EL MAX VERE QUE ONDA SI LO HAGO HASH
//AHORA NO ES LO Q IMPORTA
ECBucket dirIdList[LIST_SIZE];
Direction directions[MAX_ENTITIES];
int dirCompAmount;

int get_direction_component_amount(){
    return dirCompAmount;
}

Direction* get_direction_by_index(int indx){
    return &directions[indx];
}

Direction* get_id_associated_direction(int id){
    int dir_index = get_component_index_by_id_no_warning(dirIdList, id);
    if (dir_index == -1){
	return NULL;
    }
    return &directions[dir_index];
}

int register_direction(){
   Direction new; 
   new = DOWN;
   directions[dirCompAmount] = new;
   dirCompAmount ++;
   return dirCompAmount - 1;
}

void add_direction_component_to_id(int id){
    int index = register_direction();
    //if(is_ec_registered(posIdList, id) == 1){
//	printf("entity %u allready registered \n", id);
  //  }
    register_ec(dirIdList, id, index);
}

int init_direction_ecs(){
    return init_ec_hash_list(dirIdList);
}
