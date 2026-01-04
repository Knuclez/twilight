#include <stdio.h>
#include "ecs/ec_hash_list.h"
#include "ecs/target_ecs.h"


//EL DIA QUE TENGA MAS ENTITYS QUE EL MAX VERE QUE ONDA SI LO HAGO HASH
//AHORA NO ES LO Q IMPORTA
ECBucket tgtIdList[LIST_SIZE];
int targets[MAX_ENTITIES];
int tgtCompAmount;

int get_target_component_amount(){
    return tgtCompAmount;
}

int* get_targets_list(){
    return targets;
}

int get_target_by_index(int indx){
    return targets[indx];
}

int get_id_associated_target(int id){
    int index = get_component_index_by_id_no_warning(tgtIdList, id);
    if (index == -1){
	return -1;
    }
    return targets[index];
}

int register_target(int id){
   targets[tgtCompAmount] = id;
   tgtCompAmount ++;
   return tgtCompAmount - 1;
}

void add_target_component_to_id(int id, int tgt_id){
    int index = register_target(tgt_id);
    //if(is_ec_registered(posIdList, id) == 1){
//	printf("entity %u allready registered \n", id);
  //  }
    register_ec(tgtIdList, id, index);
}


//just gonna do a naive pointer removal from the main id
void remove_target_component_from_id(int id){
   int cmp_indx = get_component_index_by_id(tgtIdList,id); 

}

int init_target_ecs(){
    return init_ec_hash_list(tgtIdList);
}
